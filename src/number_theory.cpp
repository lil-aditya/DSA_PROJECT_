
#include "number_theory.hpp"
#include <cstdint>

uint64_t modexp(uint64_t base, uint64_t exp, uint64_t mod) {
    if (mod == 1) return 0;
    __uint128_t res = 1;
    __uint128_t b = base % mod;
    while (exp) {
        if (exp & 1) res = (res * b) % mod;
        b = (b * b) % mod;
        exp >>= 1;
    }
    return (uint64_t)res;
}

// extended gcd for integers (returns gcd and sets x,y so that ax+by=gcd)
uint64_t egcd(uint64_t a, uint64_t b, int64_t &x, int64_t &y) {
    if (a == 0) { x = 0; y = 1; return b; }
    int64_t x1 = 0, y1 = 0;
    uint64_t g = egcd(b % a, a, x1, y1);
    x = y1 - (int64_t)(b / a) * x1;
    y = x1;
    return g;
}

int64_t modInverse(int64_t a, int64_t m) {
    int64_t x = 0, y = 0;
    uint64_t g = egcd((uint64_t)a, (uint64_t)m, x, y);
    if (g != 1) return -1; // inverse doesn't exist
    int64_t res = x % (int64_t)m;
    if (res < 0) res += m;
    return res;
}


//optinal just for __uint128_t




/**
 * src/number_theory.cpp (Add this function)
 * @brief Calculates (a * b) % mod safely without relying on __uint128_t 
 * (though you don't need it since you use 128-bit types).
 * Uses the binary multiplication method.
 */
uint64_t modMul(uint64_t a, uint64_t b, uint64_t mod) {
    uint64_t res = 0;
    a = a % mod;
    while (b > 0) {
        // If the least significant bit of b is 1
        if (b & 1) {
            // Add 'a' to the result and take the modulus
            res = (res + a) % mod;
        }
        // Double 'a' for the next bit position
        a = (a * 2) % mod;
        // Move to the next bit of 'b'
        b >>= 1; // Same as b = b / 2;
    }
    return res;
}
