
// #pragma once
// #include <cstdint>

// uint64_t modexp(uint64_t base, uint64_t exp, uint64_t mod);
// uint64_t egcd(uint64_t a, uint64_t b, int64_t &x, int64_t &y);
// int64_t modInverse(int64_t a, int64_t m);

#pragma once
#include <cstdint>

// This is your existing function (same as modPow)
uint64_t modexp(uint64_t base, uint64_t exp, uint64_t mod); 

// These are your other existing functions
uint64_t egcd(uint64_t a, uint64_t b, int64_t &x, int64_t &y);
int64_t modInverse(int64_t a, int64_t m);

/**
 * @brief Calculates (a * b) % mod safely without overflowing 64-bit.
 * --- THIS IS THE NEW LINE YOU NEED TO ADD ---
 */
uint64_t modMul(uint64_t a, uint64_t b, uint64_t mod);
