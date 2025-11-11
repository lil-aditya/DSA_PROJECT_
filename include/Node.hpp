#pragma once

#include <string>
#include <thread>
#include <mutex>
#include <map>
#include <memory>

#include "priority_engine.hpp"
#include "graph_routing.hpp"
#include "rsa_signature.hpp"
#include "hashmap.hpp"
#include "logger.hpp"
#include "json.hpp"  // <-- Place the nlohmann single-header here
#include "httplib.h" // <-- Place the cpp-httplib single-header here

class Node
{
public:
    Node(int id, const std::string &name);
    ~Node();

    void start();
    void stop();

    // Threads
    void runServer();
    void runWorker();
    void processPacket(const DataPacket &packet);

    void logEvent(const std::string &event);

    // Node identity & state
    int nodeID;
    std::string nodeName;
    Keys nodeKeys;
    Graph *networkMap = nullptr;        // pointer to global network graph
    MetadataMap *addressBook = nullptr; // pointer to global metadata map (public keys)
    PriorityEngine inbox;               // the node's inbox

    // Concurrency / networking
    httplib::Server server;
    std::thread serverThread;
    std::thread workerThread;
    std::mutex inboxMutex;
    // keep a small in-memory event log for frontend polling (GET /events)
    std::vector<std::string> eventLog;
    std::mutex eventMutex;
    bool running = true;

    // Port mapping for nodes -> ports
    static std::map<int, int> portMap;
};
