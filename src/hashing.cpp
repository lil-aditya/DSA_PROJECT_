
#include "hashing.hpp"
#include <cstdint>
#include <string>

// Simple non-cryptographic rolling hash for demo purposes only.
uint64_t simpleHash(const std::string &data) {
    const uint64_t P = 1315423911u;
    uint64_t h = 1469598103934665603ULL;
    for (unsigned char c : data) {
        h ^= (uint64_t)c;
        h *= P;
    }
    return h;
}
