// /**
//  * main.cpp
//  *
//  * This is the main driver file for the ADIPE project.
//  * It's responsible for demonstrating and testing all the
//  * individual components to simulate the secure, prioritized network.
//  */

// #include <iostream>
// #include <string>
// #include <vector>
// #include <cstdint>

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
    
//     // Assumes your rsa_signature.hpp has 'Keys' and 'generateKeys'
//     Keys keys = generateKeys(); 
//     std::cout << "RSA n: " << keys.n << " e: " << keys.e << " d: " << keys.d << std::endl;

//     // Using "CriticalDataPacket-Example" from your log, not "..."
//     std::string data = "CriticalDataPacket-Example";
//     std::cout << "Data: \"" << data << "\"" << std::endl;

//     // Assumes your rsa_signature.hpp has 'simpleHash'
//     uint64_t hash = simpleHash(data);
//     std::cout << "Hash: " << hash << std::endl;

//     // Assumes your rsa_signature.hpp has 'signData'
//     uint64_t signature = signData(data, keys);
//     std::cout << "Signature: " << signature << std::endl;

//     // Assumes your rsa_signature.hpp has 'verifySignature'
//     bool verified = verifySignature(data, signature, keys);
    
//     // Debugging hash
//     uint64_t verified_hash = modexp(signature, keys.e, keys.n);
//     std::cout << "Verified Hash: " << verified_hash << std::endl;
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
//     //          This is the standard C++ way to use a priority_queue:
//     //          1. check 'top()' to see the item
//     //          2. call 'pop()' to remove it
//     while (!pq.empty()) {
//         // Assumes your PriorityEngine has a 'top()' member
//         DataPacket p = pq.pop(); 
//         pq.pop(); // Assumes 'pop()' just removes the item
        
//         // ** FIX 5: Use 'p.id' and 'p.urgency' from your 'DataPacket' struct **
//         std::cout << " - \"" << p.id << "\" (urgency=" << p.urgency << ")" << std::endl;
//     }
//     std::cout << std::endl;


//     // --- 5. Graph Routing (BFS) Test ---
//     std::cout << "--- 5. Graph Routing (BFS) Test ---" << std::endl;
    
//     Graph g(6); 
//     g.addEdge(0, 1);
//     g.addEdge(0, 2);
//     g.addEdge(1, 3);
//     g.addEdge(2, 4);
//     g.addEdge(3, 5); // Corrected from 4,5 in your old code to 3,5 to make a path

//     std::cout << "BFS order from node 0: ";
//     g.BFS(0); 
//     std::cout << std::endl;

//     // ** FIX 6: Your Graph class does not have 'findShortestPath' **
//     // We will comment this out until you implement it.
//     /*
//     std::cout << "Shortest path from 0 to 5: ";
//     std::vector<int> path = g.findShortestPath(0, 5);
//     for (int node : path) {
//         std::cout << node << " ";
//     }
//     std::cout << std::endl;
//     */
    
//     std::cout << std::endl;


//     std::cout << "--- END ---" << std::endl;
//     return 0;
// }

/**
 * main.cpp
 *
 * This is the main driver file for the ADIPE project.
 * It's responsible for demonstrating and testing all the
 * individual components to simulate the secure, prioritized network.
 */

#include <iostream>
#include <string>
#include <vector>
#include <cstdint>

// All the project components
#include "number_theory.hpp"
#include "hashing.hpp"
#include "rsa_signature.hpp"
#include "hashmap.hpp"
#include "priority_engine.hpp"
#include "graph_routing.hpp"

// This is needed for the 'DataPacket' struct (which you used in your old main.cpp)
// This struct definition is probably inside "priority_engine.hpp"
// If not, you may need to define it here or in its own header.
// (Assuming your DataPacket struct looks like this based on your old code)


int main() {
    std::cout << "--- ADIPE DEMO (Toy) ---" << std::endl << std::endl;

    // --- 0. Number Theory Test ---
    std::cout << "--- 0. Number Theory Test ---" << std::endl;
    uint64_t test_result = modexp(5, 3, 13); // Using your function name 'modexp'
    std::cout << "Test (5^3) % 13: " << test_result << " (Expected: 8) ... ";
    std::cout << (test_result == 8 ? "PASS" : "FAIL") << std::endl;
    std::cout << std::endl;


    // --- 1. & 2. RSA & Hash Test ---
    std::cout << "--- 1. & 2. RSA & Hash Test ---" << std::endl;
    
    // Assumes your rsa_signature.hpp has 'Keys' and 'generateKeys'
    Keys keys = generateKeys(); 
    std::cout << "RSA n: " << keys.n << " e: " << keys.e << " d: " << keys.d << std::endl;

    // Using "CriticalDataPacket-Example" from your log, not "..."
    std::string data = "CriticalDataPacket-Example";
    std::cout << "Data: \"" << data << "\"" << std::endl;

    // Assumes your rsa_signature.hpp has 'simpleHash'
    uint64_t hash = simpleHash(data);
    std::cout << "Hash: " << hash << std::endl;

    // Assumes your rsa_signature.hpp has 'signData'
    uint64_t signature = signData(data, keys);
    std::cout << "Signature: " << signature << std::endl;

    // Assumes your rsa_signature.hpp has 'verifySignature'
    bool verified = verifySignature(data, signature, keys);
    
    // Debugging hash
    uint64_t verified_hash = modexp(signature, keys.e, keys.n);
    std::cout << "Verified Hash: " << verified_hash << std::endl;
    std::cout << "Signature verification: " << (verified ? "PASS" : "FAIL") << std::endl;
    std::cout << std::endl;


    // --- 3. Metadata Store Test ---
    std::cout << "--- 3. Metadata Store Test ---" << std::endl;
    MetadataMap meta;
    meta.insert("UserA_pub", "pubkey_userA_example");
    meta.insert("UserB_pub", "pubkey_userB_example");
    std::cout << "Inserted UserA_pub and UserB_pub" << std::endl;

    // ** FIX 1: Your function was named 'get', not 'lookup' **
    std::string pubkey = meta.get("UserA_pub"); 
    std::cout << "Lookup UserA_pub: " << pubkey << " ... ";
    std::cout << (pubkey == "pubkey_userA_example" ? "PASS" : "FAIL") << std::endl;
    std::cout << std::endl;


    // --- 4. Priority Engine Test ---
    std::cout << "--- 4. Priority Engine Test ---" << std::endl;
    PriorityEngine pq;

    // ** FIX 2: Your struct is 'DataPacket', not 'Packet' **
    // Using { } initializer list as seen in your old code
    pq.push(DataPacket{"pkt1", 10});
    pq.push(DataPacket{"pkt2", 5});
    pq.push(DataPacket{"pkt3", 20});

    std::cout << "Processing Packets by urgency (highest first):" << std::endl;
    
    // ** FIX 3: Your function is 'empty()', not 'isEmpty()' **
    // ** FIX 4: Your 'pop()' likely returns 'std::optional' or just removes.
    //         This is the standard C++ way to use a priority_queue:
    //         1. check 'top()' to see the item
    //         2. call 'pop()' to remove it
    while (!pq.empty()) {
        
        // --- ERROR FIX ---
        // 1. pq.pop() returns std::optional<DataPacket>.
        // 2. Since we checked !pq.empty(), we can safely "unwrap" the
        //    optional with the * operator to get the DataPacket inside.
        //    (Alternatively, use .value())
        DataPacket p = *pq.pop(); 
        
        // 3. We REMOVE the redundant pq.pop() call that was here.
        //    Your PriorityEngine::pop() already removes the item.
        
        // ** FIX 5: Use 'p.id' and 'p.urgency' from your 'DataPacket' struct **
        std::cout << " - \"" << p.id << "\" (urgency=" << p.urgency << ")" << std::endl;
    }
    std::cout << std::endl;


    // --- 5. Graph Routing (BFS) Test ---
    std::cout << "--- 5. Graph Routing (BFS) Test ---" << std::endl;
    
    Graph g(6); 
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);
    g.addEdge(3, 5); // Corrected from 4,5 in your old code to 3,5 to make a path

    std::cout << "BFS order from node 0: ";
    std::vector<int> order = g.BFS(0); 
    
    // 2. Loop over the vector and print each node
    for (int node : order) {
        std::cout << node << " ";
    }
    std::cout << std::endl;

    // ** FIX 6: Your Graph class does not have 'findShortestPath' **
    // We will comment this out until you implement it.
    /*
    std::cout << "Shortest path from 0 to 5: ";
    std::vector<int> path = g.findShortestPath(0, 5);
    for (int node : path) {
        std::cout << node << " ";
    }
    std::cout << std::endl;
    */
    
    std::cout << std::endl;


    std::cout << "--- END ---" << std::endl;
    return 0;
}
