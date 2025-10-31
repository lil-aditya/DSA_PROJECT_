#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <map>
#include <optional>
#include <algorithm>

#include "number_theory.hpp"
#include "hashing.hpp"
#include "rsa_signature.hpp"
#include "hashmap.hpp"
#include "priority_engine.hpp"
#include "graph_routing.hpp"
#include "logger.hpp" // ✅ our logger

// ✅ Macro for logging like cout
#define PRINT(x) logger.Log(x)

/**
 * @brief Simulates packet traversal node by node
 */
void simulatePath(std::vector<int> path, 
                  std::map<int, PriorityEngine>& nodeInboxes, 
                  MetadataMap& addressBook)
{
    if (path.empty()) {
        PRINT("SIMULATION ERROR: Path is empty.\n");
        return;
    }

    for (size_t i = 1; i < path.size(); ++i) {
        int currentNodeIdx = path[i];

        PRINT("\n--- Node " + std::to_string(currentNodeIdx) + " Processing ---\n");

        if (nodeInboxes[currentNodeIdx].empty()) {
            PRINT("ERROR: Node inbox empty. Packet lost.\n");
            break;
        }

        DataPacket packet = *nodeInboxes[currentNodeIdx].pop();
        PRINT("Popped packet " + packet.id + " (Urgency " + std::to_string(packet.urgency) + ")\n");
        PRINT("Packet data: " + packet.data + "\n");

        std::string pub_e = addressBook.get(packet.senderID + "_pub_e");
        std::string pub_n = addressBook.get(packet.senderID + "_pub_n");

        if (pub_e == "NOT_FOUND" || pub_n == "NOT_FOUND") {
            PRINT("LOOKUP FAILED: Missing public key.\n");
            break;
        }

        Keys senderPubKey;
        senderPubKey.e = std::stoull(pub_e);
        senderPubKey.n = std::stoull(pub_n);
        senderPubKey.d = 0;

        bool ok = verifySignature(packet.data, packet.signature, senderPubKey);

        if (ok) {
            PRINT("Signature VALID ✅\n");

            if (currentNodeIdx == path.back()) {
                PRINT("Packet delivered to final destination!\n");
            } else {
                int nextHop = path[i+1];
                PRINT("Forwarding to node " + std::to_string(nextHop) + "\n");
                nodeInboxes[nextHop].push(packet);
            }
        } else {
            PRINT("Signature INVALID ❌ Packet dropped.\n");
            break;
        }
    }
}

int main() {
    PRINT("--- Simulation Setup ---\n");

    Graph network(6);
    network.addEdge(0,1);
    network.addEdge(1,3);
    network.addEdge(3,5);
    network.addEdge(0,2);
    network.addEdge(2,4);
    network.addEdge(4,5);
    PRINT("Network graph created.\n");

    MetadataMap addressBook;
    Keys admin = generateKeys();
    Keys userA = admin; 

    addressBook.insert("Admin_pub_e", std::to_string(admin.e));
    addressBook.insert("Admin_pub_n", std::to_string(admin.n));
    addressBook.insert("UserA_pub_e", std::to_string(userA.e));
    addressBook.insert("UserA_pub_n", std::to_string(userA.n));

    PRINT("Address book populated.\n");

    std::map<int, PriorityEngine> nodeInboxes;
    for (int i = 0; i < 6; i++) nodeInboxes[i] = PriorityEngine();

    PRINT("Node inboxes created.\n");

    // ---- SIM 1 ----
    PRINT("\n--- Simulation 1: Valid Packet ---\n");

    std::string data = "REBOOT_SERVER_COMMAND";
    uint64_t sig = signData(data, admin);
    DataPacket pkt("admin_01", 20, data, "Admin", sig);

    std::vector<int> path1 = network.findShortestPath(0,5);
    PRINT("Path: ");
    for (int n : path1) PRINT(std::to_string(n) + " ");
    PRINT("\n");

    nodeInboxes[1].push(pkt);
    simulatePath(path1, nodeInboxes, addressBook);

    // ---- SIM 2 ----
    PRINT("\n--- Simulation 2: Tampered Packet ---\n");

    std::string d2 = "LOG_DATA_NORMAL";
    uint64_t s2 = signData(d2, userA);
    DataPacket pkt2("u02", 5, d2, "UserA", s2);
    pkt2.data = "MALICIOUS_DATA_INJECTED";

    std::vector<int> path2 = network.findShortestPath(0,4);
    PRINT("Path: ");
    for (int n : path2) PRINT(std::to_string(n) + " ");
    PRINT("\n");

    nodeInboxes[2].push(pkt2);
    simulatePath(path2, nodeInboxes, addressBook);

    PRINT("\n--- Simulation Complete ---\n");
    return 0;
}
