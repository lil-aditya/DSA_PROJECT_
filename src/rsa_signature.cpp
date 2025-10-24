#include "rsa_signature.hpp"

// Assumes your keys are generated here or in the header
Keys generateKeys() {
    Keys k;
    k.n = 1009840029511;
    k.e = 65537;//public key
    k.d = 920144150369;//private key
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
    return modexp(hash, keys.d, keys.n); // ,private,public
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