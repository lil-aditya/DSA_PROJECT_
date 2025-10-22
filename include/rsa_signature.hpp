
#pragma once
#include <cstdint>
#include <string>
struct RSAKeys {
    uint64_t n;
    uint64_t e;
    uint64_t d;
};
RSAKeys generateRSAKeys();
uint64_t signData(uint64_t hash, const RSAKeys &keys);
uint64_t verifySignature(uint64_t signature, const RSAKeys &keys);
