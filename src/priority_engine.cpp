
#include "priority_engine.hpp"
#include <iostream>

void PriorityEngine::push(const DataPacket &p) {
    pq.push(PQItem{p.urgency, p.id});
}

std::optional<DataPacket> PriorityEngine::pop() {
    if (pq.empty()) return std::nullopt;
    PQItem it = pq.top(); pq.pop();
    return DataPacket{it.id, it.urgency};
}

bool PriorityEngine::empty() const { return pq.empty(); }
size_t PriorityEngine::size() const { return pq.size(); }
