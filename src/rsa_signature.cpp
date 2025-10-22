
#include "rsa_signature.hpp"
#include "number_theory.hpp"
#include <cstdint>
#include <iostream>

// For simplicity the demo uses small fixed primes.
// In real use, generate large primes (use bibliotheca like GMP/OpenSSL).
static const uint64_t P = 1000003ULL; // prime
static const uint64_t Q = 1009837ULL; // prime

RSAKeys generateRSAKeys() {
    uint64_t n = P * Q;
    uint64_t phi = (P - 1) * (Q - 1);
    uint64_t e = 65537;
    int64_t d = modInverse((int64_t)e, (int64_t)phi);
    if (d == -1) {
        std::cerr << "Failed to compute modular inverse for RSA d\n";
        d = 1;
    }
    return RSAKeys{n, e, (uint64_t)d};
}

uint64_t signData(uint64_t hash, const RSAKeys &keys) {
    return modexp(hash, keys.d, keys.n);
}

uint64_t verifySignature(uint64_t signature, const RSAKeys &keys) {
    return modexp(signature, keys.e, keys.n);
}
