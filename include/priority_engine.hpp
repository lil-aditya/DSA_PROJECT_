
#pragma once
#include <queue>
#include <string>
#include <experimental/optional>

struct DataPacket {
    std::string id;
    uint32_t urgency; // higher => more urgent
};

struct PQItem {
    uint32_t urgency;
    std::string id;
    bool operator<(const PQItem &o) const { return urgency < o.urgency; } // max-heap
};

class PriorityEngine {
    std::priority_queue<PQItem> pq;
public:
    void push(const DataPacket &p);
    std::experimental::optional<DataPacket> pop();
    bool empty() const;
    size_t size() const;
};
