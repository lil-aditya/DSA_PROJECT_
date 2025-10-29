
#include "priority_engine.hpp"
#include <iostream>
using namespace std;

void PriorityEngine::push(const DataPacket &p) {
    pq.push(p);
}

optional<DataPacket> PriorityEngine::pop() {
    if (pq.empty()) return nullopt;
    DataPacket high_priority_packet =pq.top(); pq.pop();
    return high_priority_packet;
}

bool PriorityEngine::empty() const { return pq.empty(); }
size_t PriorityEngine::size() const { return pq.size(); }
