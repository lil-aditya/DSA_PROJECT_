
#pragma once
#include <queue>
#include <string>
#include <optional>
#include <cstdint>
using namespace std;
struct DataPacket {
    string id;
    uint32_t urgency; // higher => more urgent
    string data;     // The actual message, e.g., "REBOOT_SERVER"
    string senderID; // Who sent it, e.g., "Admin"
    uint64_t signature;

    DataPacket(const string& i, uint32_t u, const string& d, 
               const string& s, uint64_t sig)
        : id(i), urgency(u), data(d), senderID(s), signature(sig) {}

    // This tells the priority_queue how to sort
    bool operator<(const DataPacket& other) const {
        return urgency < other.urgency; // Lower number = lower priority
    }
};

class PriorityEngine {
private:
    priority_queue<DataPacket> pq;
public:
    void push(const DataPacket &p);
    optional<DataPacket> pop();
    bool empty() const;
    size_t size() const;
};
