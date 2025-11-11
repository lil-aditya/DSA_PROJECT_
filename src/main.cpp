// Launcher for Phase 3: instantiate nodes, start servers/workers, inject a test packet.

#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

#include "graph_routing.hpp"
#include "hashmap.hpp"
#include "rsa_signature.hpp"
#include "logger.hpp"
#include "Node.hpp"

int main()
{
    logger.Log("--- Phase 3 Launcher: Starting nodes ---\n");

    // Build network graph
    Graph network(6);
    network.addEdge(0, 1);
    network.addEdge(1, 3);
    network.addEdge(3, 5);
    network.addEdge(0, 2);
    network.addEdge(2, 4);
    network.addEdge(4, 5);

    // Address book (public keys)
    MetadataMap addressBook;
    Keys admin = generateKeys();
    // for demo we reuse keys; in real deploy every node has unique keys
    for (int i = 0; i < 6; ++i)
    {
        addressBook.insert("Node" + std::to_string(i) + "_pub_e", std::to_string(admin.e));
        addressBook.insert("Node" + std::to_string(i) + "_pub_n", std::to_string(admin.n));
    }

    // Create nodes
    std::vector<std::unique_ptr<Node>> nodes;
    for (int i = 0; i < 6; ++i)
    {
        nodes.emplace_back(std::make_unique<Node>(i, "Node" + std::to_string(i)));
        nodes.back()->networkMap = &network;
        nodes.back()->addressBook = &addressBook;
        nodes.back()->nodeKeys = admin; // demo only
    }

    // Start all nodes
    for (auto &n : nodes)
        n->start();

    // Give servers time to come up
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // Inject a test packet into Node 0 using httplib::Client
    {
        std::string data = "REBOOT_SERVER_COMMAND";
        uint64_t sig = signData(data, admin);
        DataPacket pkt("test_01", 50, data, "Node0", sig, 5); // destination = node 5

        try
        {
            httplib::Client cli("localhost", Node::portMap[0]);
            nlohmann::json j = pkt;
            cli.Post("/packet", j.dump(), "application/json");
            logger.Log("Injected test packet to Node 0\n");
        }
        catch (...)
        {
            logger.Log("Failed to inject test packet (httplib client not available).\n");
        }
    }

    // Keep main alive to let nodes process; in a real app you'd use a nicer shutdown signal
    std::this_thread::sleep_for(std::chrono::seconds(10));

    // Stop nodes
    for (auto &n : nodes)
        n->stop();

    logger.Log("--- Launcher shutdown ---\n");
    return 0;
}
