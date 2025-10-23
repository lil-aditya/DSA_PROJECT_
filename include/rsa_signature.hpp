
// #pragma once
// #include <cstdint>
// #include <string>
// struct RSAKeys {
//     uint64_t n;
//     uint64_t e;
//     uint64_t d;
// };
// RSAKeys generateRSAKeys();
// uint64_t signData(uint64_t hash, const RSAKeys &keys);
// uint64_t verifySignature(uint64_t signature, const RSAKeys &keys);

#pragma once

#include <cstdint>
#include <string>
#include "hashing.hpp"        // Needs the hash function
#include "number_theory.hpp"  // Needs modexp

// A simple struct to hold the keys
struct Keys {
    uint64_t n;
    uint64_t e; // Public exponent
    uint64_t d; // Private exponent
};

/**
 * @brief Generates the hard-coded "toy" keys for the demo.
 */
Keys generateKeys();

/**
 * @brief Signs a data string with the private key.
 * @param data The data to sign.
 * @param keys The key pair.
 * @return The 64-bit signature.
 */
uint64_t signData(const std::string& data, const Keys& keys);

/**
 * @brief Verifies a signature using the public key.
 * @param data The original data.
 * @param signature The received signature.
 * @param keys The key pair.
 * @return true if the signature is valid, false otherwise.
 */
bool verifySignature(const std::string& data, uint64_t signature, const Keys& keys);
