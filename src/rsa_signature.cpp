
// // #include "rsa_signature.hpp"
// // #include "number_theory.hpp"
// // #include <cstdint>
// // #include <iostream>

// // // For simplicity the demo uses small fixed primes.
// // // In real use, generate large primes (use bibliotheca like GMP/OpenSSL).
// // static const uint64_t P = 1000003ULL; // prime
// // static const uint64_t Q = 1009837ULL; // prime

// // RSAKeys generateRSAKeys() {
// //     uint64_t n = P * Q;
// //     uint64_t phi = (P - 1) * (Q - 1);
// //     uint64_t e = 65537;
// //     int64_t d = modInverse((int64_t)e, (int64_t)phi);
// //     if (d == -1) {
// //         std::cerr << "Failed to compute modular inverse for RSA d\n";
// //         d = 1;
// //     }
// //     return RSAKeys{n, e, (uint64_t)d};
// // }

// // uint64_t signData(uint64_t hash, const RSAKeys &keys) {
// //     return modexp(hash, keys.d, keys.n);
// // }

// // uint64_t verifySignature(uint64_t signature, const RSAKeys &keys) {
// //     return modexp(signature, keys.e, keys.n);
// // }
// #include "rsa_signature.hpp"

// // This function creates the *exact* keys from your log file.
// Keys generateKeys() {
//     // p = 1004909, q = 1004911
//     // These are the prime factors of your 'n'.
    
//     Keys k;
//     k.n = 1009840029511;     // n = p * q
//     k.e = 65537;               // Public exponent (from your log)
    
//     // phi = (p-1) * (q-1) = 1009838019692
//     // d = modInverse(e, phi)
//     k.d = 920144150369;      // Private exponent (from your log)
    
//     return k;
// }

// /**
//  * Signs the data.
//  * 1. Hashes the data.
//  * 2. Encrypts the hash with the PRIVATE key (d).
//  */
// uint64_t signData(const std::string& data, const Keys& keys) {
//     // 1. Get the hash
//     uint64_t hash = simpleHash(data)% keys.n;

//     // 2. Encrypt the hash with the PRIVATE key (d)
//     // This is the signature.
//     // We use your 'modexp' function from number_theory.
//     return modexp(hash, keys.d, keys.n);
// }

// /**
//  * Verifies the signature.
//  * 1. Re-hashes the original data.
//  * 2. Decrypts the signature with the PUBLIC key (e).
//  * 3. Compares the two hashes.
//  */
// bool verifySignature(const std::string& data, uint64_t signature, const Keys& keys) {
//     // 1. Re-hash the data to get what we expect.
//     uint64_t expectedHash = simpleHash(data)% keys.n;

//     // 2. Decrypt the signature with the PUBLIC key (e).
//     // This gives us the hash the sender signed.
//     uint64_t decryptedHash = modexp(signature, keys.e, keys.n);

//     // 3. Compare the hashes.
//     return expectedHash == decryptedHash;
// }

#include "rsa_signature.hpp"

// Assumes your keys are generated here or in the header
Keys generateKeys() {
    Keys k;
    k.n = 1009840029511;
    k.e = 65537;
    k.d = 920144150369;
    return k;
}

/**
 * Signs the data.
 * 1. Hashes the data (mod n).
 * 2. Encrypts the hash with the PRIVATE key (d).
 */
uint64_t signData(const std::string& data, const Keys& keys) {
    // 1. Get the hash AND apply the modulus
    uint64_t hash = simpleHash(data) % keys.n; 
    
    // 2. SIGN WITH THE PRIVATE KEY (d)
    return modexp(hash, keys.d, keys.n); 
}

/**
 * Verifies the signature.
 * 1. Re-hashes the original data (mod n).
 * 2. Decrypts the signature with the PUBLIC key (e).
 * 3. Compares the two hashes.
 */
bool verifySignature(const std::string& data, uint64_t signature, const Keys& keys) {
    // 1. Re-hash the data to get what we expect
    uint64_t expectedHash = simpleHash(data) % keys.n;
    
    // 2. VERIFY WITH THE PUBLIC KEY (e)
    uint64_t decryptedHash = modexp(signature, keys.e, keys.n); 
    
    // 3. This will now correctly return true or false.
    return expectedHash == decryptedHash;
}