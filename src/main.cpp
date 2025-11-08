// // #include <iostream>
// // #include <string>
// // #include <vector>
// // #include <cstdint>
// // #include <map>
// // #include <optional>
// // #include <algorithm>

// // #include "number_theory.hpp"
// // #include "hashing.hpp"
// // #include "rsa_signature.hpp"
// // #include "hashmap.hpp"
// // #include "priority_engine.hpp"
// // #include "graph_routing.hpp"
// // #include "logger.hpp" // ✅ our logger

// // // ✅ Macro for logging like cout
// // #define PRINT(x) logger.Log(x)

// // /**
// //  * @brief Simulates packet traversal node by node
// //  */
// // void simulatePath(std::vector<int> path, 
// //                   std::map<int, PriorityEngine>& nodeInboxes, 
// //                   MetadataMap& addressBook)
// // {
// //     if (path.empty()) {
// //         PRINT("SIMULATION ERROR: Path is empty.\n");
// //         return;
// //     }

// //     for (size_t i = 1; i < path.size(); ++i) {
// //         int currentNodeIdx = path[i];

// //         PRINT("\n--- Node " + std::to_string(currentNodeIdx) + " Processing ---\n");

// //         if (nodeInboxes[currentNodeIdx].empty()) {
// //             PRINT("ERROR: Node inbox empty. Packet lost.\n");
// //             break;
// //         }

// //         DataPacket packet = *nodeInboxes[currentNodeIdx].pop();
// //         PRINT("Popped packet " + packet.id + " (Urgency " + std::to_string(packet.urgency) + ")\n");
// //         PRINT("Packet data: " + packet.data + "\n");

// //         std::string pub_e = addressBook.get(packet.senderID + "_pub_e");
// //         std::string pub_n = addressBook.get(packet.senderID + "_pub_n");

// //         if (pub_e == "NOT_FOUND" || pub_n == "NOT_FOUND") {
// //             PRINT("LOOKUP FAILED: Missing public key.\n");
// //             break;
// //         }

// //         Keys senderPubKey;
// //         senderPubKey.e = std::stoull(pub_e);
// //         senderPubKey.n = std::stoull(pub_n);
// //         senderPubKey.d = 0;

// //         bool ok = verifySignature(packet.data, packet.signature, senderPubKey);

// //         if (ok) {
// //             PRINT("Signature VALID ✅\n");

// //             if (currentNodeIdx == path.back()) {
// //                 PRINT("Packet delivered to final destination!\n");
// //             } else {
// //                 int nextHop = path[i+1];
// //                 PRINT("Forwarding to node " + std::to_string(nextHop) + "\n");
// //                 nodeInboxes[nextHop].push(packet);
// //             }
// //         } else {
// //             PRINT("Signature INVALID ❌ Packet dropped.\n");
// //             break;
// //         }
// //     }
// // }

// // int main() {
// //     PRINT("--- Simulation Setup ---\n");

// //     Graph network(6);
// //     network.addEdge(0,1);
// //     network.addEdge(1,3);
// //     network.addEdge(3,5);
// //     network.addEdge(0,2);
// //     network.addEdge(2,4);
// //     network.addEdge(4,5);
// //     PRINT("Network graph created.\n");

// //     MetadataMap addressBook;
// //     Keys admin = generateKeys();
// //     Keys userA = admin; 

// //     addressBook.insert("Admin_pub_e", std::to_string(admin.e));
// //     addressBook.insert("Admin_pub_n", std::to_string(admin.n));
// //     addressBook.insert("UserA_pub_e", std::to_string(userA.e));
// //     addressBook.insert("UserA_pub_n", std::to_string(userA.n));

// //     PRINT("Address book populated.\n");

// //     std::map<int, PriorityEngine> nodeInboxes;
// //     for (int i = 0; i < 6; i++) nodeInboxes[i] = PriorityEngine();

// //     PRINT("Node inboxes created.\n");

// //     // ---- SIM 1 ----
// //     PRINT("\n--- Simulation 1: Valid Packet ---\n");

// //     std::string data = "REBOOT_SERVER_COMMAND";
// //     uint64_t sig = signData(data, admin);
// //     DataPacket pkt("admin_01", 20, data, "Admin", sig);

// //     std::vector<int> path1 = network.findShortestPath(0,5);
// //     PRINT("Path: ");
// //     for (int n : path1) PRINT(std::to_string(n) + " ");
// //     PRINT("\n");

// //     nodeInboxes[1].push(pkt);
// //     simulatePath(path1, nodeInboxes, addressBook);

// //     // ---- SIM 2 ----
// //     PRINT("\n--- Simulation 2: Tampered Packet ---\n");

// //     std::string d2 = "LOG_DATA_NORMAL";
// //     uint64_t s2 = signData(d2, userA);
// //     DataPacket pkt2("u02", 5, d2, "UserA", s2);
// //     pkt2.data = "MALICIOUS_DATA_INJECTED";

// //     std::vector<int> path2 = network.findShortestPath(0,4);
// //     PRINT("Path: ");
// //     for (int n : path2) PRINT(std::to_string(n) + " ");
// //     PRINT("\n");

// //     nodeInboxes[2].push(pkt2);
// //     simulatePath(path2, nodeInboxes, addressBook);

// //     PRINT("\n--- Simulation Complete ---\n");
// //     return 0;
// // }

// /**
//  * main.cpp (Phase 3 - The Launcher)
//  *
//  * This program's ONLY job is to:
//  * 1. Set up the shared network resources (Graph, Address Book).
//  * 2. Create and launch all 6 independent Node servers.
//  * 3. Keep the main thread alive so the node threads can run.
//  *
//  * All simulation logic is now handled inside the Node class.
//  */

// // --- C++ Libraries ---
// #include <iostream>
// #include <vector>
// #include <string>
// #include <chrono> // For std::this_thread::sleep_for
// #include <thread> // For std::this_thread::sleep_for

// // --- Our Project Headers ---
// #include "Node.hpp"            // The new "Brain" class
// #include "graph_routing.hpp" // The global network map
// #include "hashmap.hpp"       // The global address book

// int main() {
//     // --- 1. Simulation Setup ---
//     std::cout << "--- ADIPE Network Engine ---" << std::endl;
//     std::cout << "[Setup] Setting up world..." << std::endl;

//     // Create the global, shared network map
//     Graph network(6); // 6 nodes, 0-5
//     network.addEdge(0, 1);
//     network.addEdge(1, 3);
//     network.addEdge(3, 5);
//     network.addEdge(0, 2);
//     network.addEdge(2, 4);
//     network.addEdge(4, 5);
//     std::cout << "[Setup] Network graph created." << std::endl;

//     // Create the global, shared address book
//     MetadataMap addressBook;
//     std::cout << "[Setup] Global address book created." << std::endl;

//     // --- 2. Create and Start all Nodes ---
    
//     // We create a vector to hold our 6 node objects
//     std::vector<Node> nodes;
//     for (int i = 0; i < 6; ++i) {
//         // emplace_back constructs the Node in-place, passing the
//         // global map and book as references.
//         nodes.emplace_back(i, network, addressBook);
//     }
//     stdD::cout << "[Setup] All 6 nodes created." << std::endl;

//     // Start all node threads (server + worker)
//     for (auto& node : nodes) {
//         node.start(); // This launches the node's threads
//     }
    
//     std::cout << "\n--- C++ Network Engine is LIVE ---" << std::endl;
//     std::cout << "All nodes running. Awaiting packets via Python API..." << std::endl;
//     std::cout << "Python API (Node 0) should connect to port " << NODE_PORTS.at(0) << "." << std::endl;

//     // --- 3. Keep the Main Thread Alive ---
//     // If main() exits, the entire program (and all node threads)
//     // will be terminated. We must keep it running forever.
//     while (true) {
//         // Sleep for a long time to prevent this loop from
//         // using any CPU power.
//         std::this_thread::sleep_for(std::chrono::seconds(60));
//     }

//     return 0; // This line will never be reached
// }

/**
 * main.cpp (Phase 3 - The Launcher)
 *
 * This program's ONLY job is to:
 * 1. Set up the shared network resources (Graph, Address Book).
 * 2. Create and launch all 6 independent Node servers.
 * 3. Keep the main thread alive so the node threads can run.
 */

// --- C++ Libraries ---
#include <iostream>
#include <vector>
#include <string>
#include <chrono> // For std::this_thread::sleep_for
#include <thread> // For std::this_thread::sleep_for
#include <map>
#include <memory> // 👈 ADD THIS for std::unique_ptr and std::make_unique

// --- Our Project Headers ---
#include "Node.hpp"            // The new "Brain" class
#include "graph_routing.hpp" // The global network map
#include "hashmap.hpp"       // The global address book
#include "logger.hpp"        // Your logger
#include "rsa_signature.hpp" // For generateKeys()

// --- DEFINE THE GLOBAL LOGGER MACRO ---
#define PRINT(x) logger.Log(x)

// --- DEFINE THE GLOBAL PORT MAP ---
// This DEFINES the map that Node.hpp declared as 'extern'.
// This is the *only* place it is created.
std::map<int, int> NODE_PORTS = {
    {0, 8080},
    {1, 8081},
    {2, 8082},
    {3, 8083},
    {4, 8084},
    {5, 8085}
};


int main() {
    // --- 1. Simulation Setup ---
    PRINT("--- ADIPE Network Engine ---\n");
    PRINT("[Setup] Setting up world...\n");

    // Create the global, shared network map
    Graph network(6); // 6 nodes, 0-5
    network.addEdge(0, 1);
    network.addEdge(1, 3);
    network.addEdge(3, 5);
    network.addEdge(0, 2);
    network.addEdge(2, 4);
    network.addEdge(4, 5);
    PRINT("[Setup] Network graph created.\n");

    // Create the global, shared address book
    MetadataMap addressBook;
    PRINT("[Setup] Global address book created.\n");

    // --- 2. Create and Start all Nodes ---
    
    // ⬇️ --- FIX 2, CHANGE 1: Store unique_ptrs, not Nodes --- ⬇️
    std::vector<std::unique_ptr<Node>> nodes;

    for (int i = 0; i < 6; ++i) {
        // ⬇️ --- FIX 2, CHANGE 2: Use push_back and std::make_unique --- ⬇️
        // This creates the Node on the heap and stores a
        // movable, non-copyable pointer to it in the vector.
        nodes.push_back(std::make_unique<Node>(i, network, addressBook));
    }
    PRINT("[Setup] All 6 nodes created.\n");

    // Start all node threads (server + worker)
    for (auto& node_ptr : nodes) { // 👈 (variable name change)
        // ⬇️ --- FIX 2, CHANGE 3: Use the -> operator to call start --- ⬇️
        node_ptr->start(); // This launches the node's threads
    }
    
    PRINT("\n--- C++ Network Engine is LIVE ---\n");
    PRINT("All nodes running. Awaiting packets via Python API...\n");
    PRINT("Python API (Node 0) should connect to port " + std::to_string(NODE_PORTS.at(0)) + ".\n");

    // --- 3. Keep the Main Thread Alive ---
    // If main() exits, the entire program (and all node threads)
    // will be terminated. We must keep it running forever.
    while (true) {
        // Sleep for a long time to prevent this loop from
        // using any CPU power.
        std::this_thread::sleep_for(std::chrono::seconds(60));
    }

    return 0; // This line will never be reached
}