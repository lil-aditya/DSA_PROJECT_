
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
