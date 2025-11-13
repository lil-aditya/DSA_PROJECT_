#include "../include/Node.hpp"

std::map<int, int> Node::portMap = {
    {0, 8080}, {1, 8081}, {2, 8082}, {3, 8083}, {4, 8084}, {5, 8085}};

Node::Node(int id, const std::string &name) : nodeID(id), nodeName(name) {}

Node::~Node() { stop(); }

void Node::start()
{
    running = true;
    serverThread = std::thread(&Node::runServer, this);
    workerThread = std::thread(&Node::runWorker, this);
}

void Node::stop()
{
    running = false;
    try
    {
        if (serverThread.joinable())
            serverThread.join();
    }
    catch (...)
    {
    }
    try
    {
        if (workerThread.joinable())
            workerThread.join();
    }
    catch (...)
    {
    }
}

void Node::runServer()
{
    // API: Receive a packet
    server.Post("/packet", [&](const httplib::Request &req, httplib::Response &res)
                {
        // Add CORS header so browser frontends can POST here
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");

        // Deserialize the packet (expects nlohmann::json)
        try {
            std::lock_guard<std::mutex> lock(inboxMutex);
            auto j = nlohmann::json::parse(req.body);
            DataPacket packet = j.get<DataPacket>();
            inbox.push(packet);
            logEvent("📩 Node " + std::to_string(nodeID) + " received packet from " + packet.senderID);
        } catch (...) {
            logEvent("❌ Failed to parse incoming packet on Node " + std::to_string(nodeID));
        }
        res.set_content("OK", "text/plain"); });

    // Preflight support for browser requests
    server.Options("/packet", [&](const httplib::Request &req, httplib::Response &res)
                   {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");
        res.set_header("Access-Control-Allow-Methods", "POST, OPTIONS");
        res.set_content("", "text/plain"); });

    // Development-only endpoint: accept packets without signature verification.
    // Useful for UI-driven testing. This endpoint should NOT be used in production.
    server.Post("/packet-dev", [&](const httplib::Request &req, httplib::Response &res)
                {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");
        try {
            std::lock_guard<std::mutex> lock(inboxMutex);
            auto j = nlohmann::json::parse(req.body);
            // Map JSON fields to DataPacket where possible; missing fields get defaults
            DataPacket packet;
            if (j.contains("id")) packet.id = j["id"].get<std::string>();
            if (j.contains("urgency")) packet.urgency = j["urgency"].get<int>();
            if (j.contains("data")) packet.data = j["data"].get<std::string>();
                packet.senderID = nodeName; // ensure sender key lookup exists in addressBook
            if (j.contains("signature")) packet.signature = j["signature"].get<uint64_t>();
            if (j.contains("destinationID")) packet.destinationID = j["destinationID"].get<int>();
                // sign the packet with this node's private key to make it pass verification
                try {
                    packet.signature = signData(packet.data, nodeKeys);
                } catch (...) {
                }
            inbox.push(packet);
            // Extract sender name from frontend if provided
            std::string senderName = packet.senderID;
            if (j.contains("sender")) {
                senderName = j["sender"].get<std::string>();
            }
            logEvent("📩 [DEV] Node " + std::to_string(nodeID) + " received dev-packet from " + senderName);
        } catch (...) {
            logEvent("❌ [DEV] Failed to parse incoming dev-packet on Node " + std::to_string(nodeID));
        }
        res.set_content("OK", "text/plain"); });

    server.Options("/packet-dev", [&](const httplib::Request &req, httplib::Response &res)
                   {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");
        res.set_header("Access-Control-Allow-Methods", "POST, OPTIONS");
        res.set_content("", "text/plain"); });

    // API: simple polling endpoint for frontend live updates
    server.Get("/events", [&](const httplib::Request &req, httplib::Response &res)
               {
        // Allow browser to fetch events
        res.set_header("Access-Control-Allow-Origin", "*");

        // return the recent event log as JSON array
        nlohmann::json j;
        {
            std::lock_guard<std::mutex> lock(eventMutex);
            j = eventLog;
        }
        res.set_content(j.dump(), "application/json"); });

    server.Options("/events", [&](const httplib::Request &req, httplib::Response &res)
                   {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "GET, OPTIONS");
        res.set_content("", "text/plain"); });

    logEvent("🚀 Node " + std::to_string(nodeID) + " running on port " + std::to_string(portMap[nodeID]));
    server.listen("localhost", portMap[nodeID]);
}

void Node::runWorker()
{
    while (running)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        std::optional<DataPacket> opt;
        {
            std::lock_guard<std::mutex> lock(inboxMutex);
            opt = inbox.pop();
        }

        if (opt)
        {
            processPacket(*opt);
        }
    }
}

void Node::processPacket(const DataPacket &packet)
{
    logEvent("⚙️ Processing packet for destination " + std::to_string(packet.destinationID));

    // Security check: verify signature using public key from addressBook
    if (addressBook == nullptr)
    {
        logEvent("❌ No addressBook available on Node " + std::to_string(nodeID));
        return;
    }

    std::string pub_e = addressBook->get(packet.senderID + "_pub_e");
    std::string pub_n = addressBook->get(packet.senderID + "_pub_n");

    if (pub_e == "NOT_FOUND" || pub_n == "NOT_FOUND")
    {
        logEvent("❌ Public key for sender not found. Dropping packet.");
        return;
    }

    Keys senderPub;
    senderPub.e = std::stoull(pub_e);
    senderPub.n = std::stoull(pub_n);
    senderPub.d = 0;

    bool valid = verifySignature(packet.data, packet.signature, senderPub);

    if (!valid)
    {
        logEvent("❌ Signature INVALID. Dropping packet.");
        return;
    }

    if (packet.destinationID == nodeID)
    {
        logEvent("✅ Packet reached Node " + std::to_string(nodeID));
        return;
    }

    // Not destination: forward to next hop (naive: send directly to destination node)
    int nextNode = packet.destinationID;
    if (portMap.find(nextNode) == portMap.end())
    {
        logEvent("❌ Unknown next node: " + std::to_string(nextNode));
        return;
    }

    int nextPort = portMap[nextNode];
    try
    {
        httplib::Client cli("localhost", nextPort);
        nlohmann::json j = packet;
        cli.Post("/packet", j.dump(), "application/json");
        logEvent("➡️ Forwarded packet to Node " + std::to_string(nextNode));
    }
    catch (...)
    {
        logEvent("❌ Failed to forward packet from Node " + std::to_string(nodeID));
    }
}

void Node::logEvent(const std::string &event)
{
    std::cout << event << std::endl;
    {
        std::lock_guard<std::mutex> lock(eventMutex);
        // keep only the last 100 events
        if (eventLog.size() > 100)
            eventLog.erase(eventLog.begin());
        nlohmann::json j = {{"nodeID", nodeID}, {"event", event}};
        eventLog.push_back(j.dump());
    }
}
