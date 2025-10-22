
#pragma once
#include <string>
#include <unordered_map>

class MetadataMap {
    std::unordered_map<std::string, std::string> table;
public:
    void insert(const std::string &key, const std::string &value);
    std::string get(const std::string &key) const;
    bool exists(const std::string &key) const;
};
