// #include <iostream>
// #include <string>
// #include <vector>
// #include <cstdint>
// #include<bits/stdc++.h>
// // All the project components
// #include "number_theory.hpp"
// #include "hashing.hpp"
// #include "rsa_signature.hpp"
// #include "hashmap.hpp"
// #include "priority_engine.hpp"
// #include "graph_routing.hpp"

// // This is needed for the 'DataPacket' struct (which you used in your old main.cpp)
// // This struct definition is probably inside "priority_engine.hpp"
// // If not, you may need to define it here or in its own header.
// // (Assuming your DataPacket struct looks like this based on your old code)
// using namespace std;

// int main() {
//     std::cout << "--- ADIPE DEMO (Toy) ---" << std::endl << std::endl;

//     // --- 0. Number Theory Test ---
//     std::cout << "--- 0. Number Theory Test ---" << std::endl;
//     uint64_t test_result = modexp(5, 3, 13); // Using your function name 'modexp'
//     std::cout << "Test (5^3) % 13: " << test_result << " (Expected: 8) ... ";
//     std::cout << (test_result == 8 ? "PASS" : "FAIL") << std::endl;
//     std::cout << std::endl;

//     // --- 1. & 2. RSA & Hash Test ---
//     std::cout << "--- 1. & 2. RSA & Hash Test ---" << std::endl;
        
//     Keys keys = generateKeys(); 
//     std::cout << "RSA n: " << keys.n << " e: " << keys.e << " d: " << keys.d << std::endl;

//     // Using "CriticalDataPacket-Example" from your log
//     std::string data = "CriticalDataPacket-Example";
//     std::cout << "Data: \"" << data << "\"" << std::endl;

//     // 1. Calculate the full hash once
//     uint64_t full_hash = simpleHash(data);

//     // 2. Calculate the hash used for crypto (Hash mod N)
//     // This is the value that must match the Verified Hash!
//     uint64_t hash_used = full_hash % keys.n;

//     // Print both hashes for clear debugging
//     std::cout << "Hash (Full 64-bit): " << full_hash << std::endl;
//     std::cout << "Hash (Mod N for Crypto): " << hash_used << std::endl; 

//     // Sign (The signData function uses the data string, not the hash variable)
//     uint64_t signature = signData(data, keys);
//     std::cout << "Signature: " << signature << std::endl;

//     // Verify 
//     bool verified = verifySignature(data, signature, keys);

//     // Debugging: Recalculate and print the decrypted hash for comparison
//     uint64_t verified_hash = modexp(signature, keys.e, keys.n);
//     std::cout << "Verified Hash: " << verified_hash << std::endl;

//     // Final status check
//     std::cout << "Signature verification: " << (verified ? "PASS" : "FAIL") << std::endl;
//     std::cout << std::endl;

//     // --- 3. Metadata Store Test ---
//     std::cout << "--- 3. Metadata Store Test ---" << std::endl;
//     MetadataMap meta;
//     meta.insert("UserA_pub", "pubkey_userA_example");
//     meta.insert("UserB_pub", "pubkey_userB_example");
//     std::cout << "Inserted UserA_pub and UserB_pub" << std::endl;

//     // ** FIX 1: Your function was named 'get', not 'lookup' **
//     std::string pubkey = meta.get("UserA_pub"); 
//     std::cout << "Lookup UserA_pub: " << pubkey << " ... ";
//     std::cout << (pubkey == "pubkey_userA_example" ? "PASS" : "FAIL") << std::endl;
//     std::cout << std::endl;


//     // --- 4. Priority Engine Test ---
//     std::cout << "--- 4. Priority Engine Test ---" << std::endl;
//     PriorityEngine pq;

//     // ** FIX 2: Your struct is 'DataPacket', not 'Packet' **
//     // Using { } initializer list as seen in your old code
//     pq.push(DataPacket{"pkt1", 10});
//     pq.push(DataPacket{"pkt2", 5});
//     pq.push(DataPacket{"pkt3", 20});

//     std::cout << "Processing Packets by urgency (highest first):" << std::endl;
    
//     // ** FIX 3: Your function is 'empty()', not 'isEmpty()' **
//     // ** FIX 4: Your 'pop()' likely returns 'std::optional' or just removes.
//     //         This is the standard C++ way to use a priority_queue:
//     //         1. check 'top()' to see the item
//     //         2. call 'pop()' to remove it
//     while (!pq.empty()) {
        
//         // --- ERROR FIX ---
//         // 1. pq.pop() returns std::optional<DataPacket>.
//         // 2. Since we checked !pq.empty(), we can safely "unwrap" the
//         //    optional with the * operator to get the DataPacket inside.
//         //    (Alternatively, use .value())
//         DataPacket p = *pq.pop(); 
        
//         // 3. We REMOVE the redundant pq.pop() call that was here.
//         //    Your PriorityEngine::pop() already removes the item.
        
//         // ** FIX 5: Use 'p.id' and 'p.urgency' from your 'DataPacket' struct **
//         std::cout << " - \"" << p.id << "\" (urgency=" << p.urgency << ")" << std::endl;
//     }
//     std::cout << std::endl;


//     // --- 5. Graph Routing (BFS) Test ---
//     cout << "--- 5. Graph Routing (BFS) Test ---" << std::endl;
    
//     Graph g(6); 
//     g.addEdge(0, 1);
//     g.addEdge(0, 2);
//     g.addEdge(1, 3);
//     g.addEdge(2, 4);
//     g.addEdge(3, 5); // Corrected from 4,5 in your old code to 3,5 to make a path

//     cout << "BFS order from node 0: ";
//     g.BFS(0);cout<<endl; 
    
//     // 2. Loop over the vector and print each node
//     // for (int node : order) {
//     //     std::cout << node << " ";
//     // }
//     // std::cout << std::endl;

//     // ** FIX 6: Your Graph class does not have 'findShortestPath' **
//     // We will comment this out until you implement it.
    
//     cout << "Shortest path from 0 to 5: ";
//     vector<int> path = g.findShortestPath(0, 5);
//     for (int node : path) {
//         std::cout << node << " ";
//     }
//     cout << endl;
    


//     cout << "--- END ---" << endl;
//     return 0;
// }




/**
 * main.cpp
 *
 * This is the new main driver file for the ADIPE project.
 * It runs the complete "Authenticated QoS" simulation
 * from end-to-end, using all components together.
 */

#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <map>
#include <optional>
#include <algorithm> // for std::reverse

// Include all your project components
#include "number_theory.hpp"
#include "hashing.hpp"
#include "rsa_signature.hpp"
#include "hashmap.hpp"
#include "priority_engine.hpp"
#include "graph_routing.hpp"

/**
 * @brief Simulates the processing of a packet at each node in its path.
 * This is the "brain" of each node.
 */
void simulatePath(std::vector<int> path, 
                  std::map<int, PriorityEngine>& nodeInboxes, 
                  MetadataMap& addressBook) 
{
    if (path.empty()) {
        std::cout << "SIMULATION ERROR: Path is empty. Cannot send packet." << std::endl;
        return;
    }

    // Start at the first hop (index 1), not the sender (index 0)
    for (size_t i = 1; i < path.size(); ++i) {
        int currentNodeIdx = path[i];
        
        std::cout << "\n--- Node " << currentNodeIdx << " Processing ---" << std::endl;
        
        if (nodeInboxes[currentNodeIdx].empty()) {
            std::cout << "ERROR: Node inbox is empty. Packet was lost." << std::endl;
            break; // Stop simulation for this packet
        }

        // 1. RECEIVE (Pop highest priority packet)
        // We can safely unwrap (*) because we checked empty()
        DataPacket packet = *nodeInboxes[currentNodeIdx].pop();
        std::cout << "Popped packet: " << packet.id 
                  << " (Urgency: " << packet.urgency 
                  << ") from " << packet.senderID << std::endl;
        std::cout << "Packet Data: \"" << packet.data << "\"" << std::endl;

        // 2. LOOKUP (Get sender's public key from "address book")
        // We assume 'n' is universal, so we only store 'e'
        std::string pub_e_str = addressBook.get(packet.senderID + "_pub_e");
        std::string pub_n_str = addressBook.get(packet.senderID + "_pub_n");

        if (pub_e_str == "NOT_FOUND" || pub_n_str == "NOT_FOUND") {
            std::cout << "LOOKUP FAILED: No public key found for " << packet.senderID << ". DROPPING." << std::endl;
            break;
        }

        // Create a temporary key object just for verification
        Keys senderPubKey;
        senderPubKey.e = std::stoull(pub_e_str); // Convert string to uint64_t
        senderPubKey.n = std::stoull(pub_n_str); // Convert string to uint64_t
        senderPubKey.d = 0; // The node does not know the private key

        // 3. VERIFY (The "Authenticated" part of QoS)
        bool isValid = verifySignature(packet.data, packet.signature, senderPubKey);

        // 4. DECISION
        if (isValid) {
            std::cout << "Signature: VALID. Packet is trusted." << std::endl;

            // Is this the final destination?
            if (currentNodeIdx == path.back()) {
                std::cout << "Packet DELIVERED to final destination (Node " << currentNodeIdx << ")." << std::endl;
            } else {
                // Forward to the next hop
                int nextHopIdx = path[i + 1];
                std::cout << "Forwarding packet to next hop: Node " << nextHopIdx << std::endl;
                nodeInboxes[nextHopIdx].push(packet);
            }
        } else {
            std::cout << "Signature: INVALID. Packet is spoofed or corrupt. DROPPING." << std::endl;
            break; // Stop forwarding this corrupt packet
        }
    }
}


int main() {
    // --- STEP 2: CREATE THE "WORLD" ---
    std::cout << "--- Simulation Setup ---" << std::endl;
    
    // 1. Create Graph (Network Topology)
    Graph network(6); // 6 nodes, 0-5
    network.addEdge(0, 1);
    network.addEdge(1, 3);
    network.addEdge(3, 5);
    network.addEdge(0, 2);
    network.addEdge(2, 4);
    network.addEdge(4, 5);
    std::cout << "Network graph created." << std::endl;

    // 2. Create Address Book and User Keys
    MetadataMap addressBook;
    Keys admin_keys = generateKeys();
    // We can use the same keys for UserA, this is just a demo
    Keys userA_keys = admin_keys; 
    
    // Store public keys (e and n) in the address book as strings
    addressBook.insert("Admin_pub_e", std::to_string(admin_keys.e));
    addressBook.insert("Admin_pub_n", std::to_string(admin_keys.n));
    addressBook.insert("UserA_pub_e", std::to_string(userA_keys.e));
    addressBook.insert("UserA_pub_n", std::to_string(userA_keys.n));
    std::cout << "Address book populated with Admin and UserA public keys." << std::endl;

    // 3. Create Node Inboxes
    std::map<int, PriorityEngine> nodeInboxes;
    for (int i = 0; i < 6; ++i) {
        nodeInboxes[i] = PriorityEngine();
    }
    std::cout << "Node inboxes (priority queues) created." << std::endl;

    
    // --- STEP 3 & 4: SIMULATION 1 (Valid Admin Packet) ---
    std::cout << "\n--- Simulation 1: Valid URGENT Packet ---" << std::endl;
    
    // 1. Admin (at Node 0) creates and signs a packet for Node 5
    std::string admin_data = "REBOOT_SERVER_COMMAND";
    uint64_t admin_sig = signData(admin_data, admin_keys);
    
    // This 5-argument constructor now matches your new .hpp file
    DataPacket admin_packet("pkt_admin_01", 20, admin_data, "Admin", admin_sig);
    
    // 2. Find Route (Using the new function from graph_routing.cpp)
    std::vector<int> path1 = network.findShortestPath(0, 5); // 0 -> 1 -> 3 -> 5
    
    std::cout << "Path found: ";
    for (int node : path1) { std::cout << node << " "; }
    std::cout << std::endl;
    
    // 3. Send (Push to first hop's inbox)
    std::cout << "Sending packet from Node 0 to Node 1..." << std::endl;
    nodeInboxes[1].push(admin_packet);

    // 4. Run the simulation
    simulatePath(path1, nodeInboxes, addressBook);


    // --- STEP 5: SIMULATION 2 (Tampered Packet - Failure Case) ---
    std::cout << "\n--- Simulation 2: Tampered LOW_PRIORITY Packet ---" << std::endl;
    
    // 1. UserA (at Node 0) creates and signs a valid packet
    std::string user_data = "LOG_DATA_NORMAL";
    uint64_t user_sig = signData(user_data, userA_keys);
    DataPacket tampered_packet("pkt_user_02", 5, user_data, "UserA", user_sig);

    // 2. *** ATTACKER TAMPERED WITH THE PACKET ***
    std::cout << "An attacker intercepts the packet and changes its data..." << std::endl;
    tampered_packet.data = "MALICIOUS_DATA_INJECTED";

    // 3. Find Route
    std::vector<int> path2 = network.findShortestPath(0, 4); // 0 -> 2 -> 4
    
    std::cout << "Path found: ";
    for (int node : path2) { std::cout << node << " "; }
    std::cout << std::endl;
    
    // 4. Send (Push to first hop's inbox)
    std::cout << "Sending tampered packet from Node 0 to Node 2..." << std::endl;
    nodeInboxes[2].push(tampered_packet);
    
    // 5. Run the simulation
    simulatePath(path2, nodeInboxes, addressBook);
    std::cout << "\n--- Simulation Complete ---" << std::endl;
    
    return 0;
}

