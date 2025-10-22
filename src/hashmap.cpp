
#include "hashmap.hpp"

void MetadataMap::insert(const std::string &key, const std::string &value) {
    table[key] = value;
}

std::string MetadataMap::get(const std::string &key) const {
    auto it = table.find(key);
    if (it == table.end()) return std::string();
    return it->second;
}

bool MetadataMap::exists(const std::string &key) const {
    return table.find(key) != table.end();
}
