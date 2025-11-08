
// #pragma once
// #include <queue>
// #include <string>
// #include <optional>
// #include <cstdint>
// using namespace std;
// struct DataPacket {
//     string id;
//     uint32_t urgency; // higher => more urgent
//     string data;     // The actual message, e.g., "REBOOT_SERVER"
//     string senderID; // Who sent it, e.g., "Admin"
//     uint64_t signature;

//     DataPacket(const string& i, uint32_t u, const string& d, 
//                const string& s, uint64_t sig)
//         : id(i), urgency(u), data(d), senderID(s), signature(sig) {}

//     // This tells the priority_queue how to sort
//     bool operator<(const DataPacket& other) const {
//         return urgency < other.urgency; // Lower number = lower priority
//     }
// };

// class PriorityEngine {
// private:
//     priority_queue<DataPacket> pq;
// public:
//     void push(const DataPacket &p);
//     optional<DataPacket> pop();
//     bool empty() const;
//     size_t size() const;
// };
#pragma once
#include <queue>
#include <string>
#include <optional>
#include <cstdint>

// --- NEW: Step 1 ---
// Include the JSON library header you downloaded
#include "json.hpp"

// Make it easy to use the json type
using json = nlohmann::json;
using namespace std;


struct DataPacket {
    string id;
    uint32_t urgency; // higher => more urgent
    string data;      // The actual message, e.g., "REBOOT_SERVER"
    string senderID;  // Who sent it, e.g., "Admin"
    uint64_t signature;

    // --- NEW: Step 2 ---
    // Add a destination for network routing
    int destinationID;

    // --- NEW: Step 3 ---
    // Add a default constructor. This is REQUIRED by the JSON library
    // to create an empty object before filling it with data.
    DataPacket() : urgency(0), signature(0), destinationID(-1) {}

    // --- MODIFIED: Step 4 ---
    // Update the main constructor to include the new destinationID
    DataPacket(const string& i, uint32_t u, const string& d, 
               const string& s, uint64_t sig, int dest)
        : id(i), urgency(u), data(d), senderID(s), signature(sig), destinationID(dest) {}

    // This tells the priority_queue how to sort (no change needed)
    bool operator<(const DataPacket& other) const {
        return urgency < other.urgency; // Lower number = lower priority
    }
};

// --- NEW: Step 5 ---
// This is the "magic" macro that tells the nlohmann/json library
// how to convert the DataPacket struct to and from a JSON string.
// It MUST list all the members of the struct.
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(DataPacket, id, urgency, data, senderID, signature, destinationID)


// --- NO CHANGES BELOW THIS LINE ---

class PriorityEngine {
private:
    priority_queue<DataPacket> pq;
public:
    void push(const DataPacket &p);
    optional<DataPacket> pop();
    bool empty() const;
    size_t size() const;
};