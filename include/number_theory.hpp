
#pragma once
#include <cstdint>

uint64_t modexp(uint64_t base, uint64_t exp, uint64_t mod);
uint64_t egcd(uint64_t a, uint64_t b, int64_t &x, int64_t &y);
int64_t modInverse(int64_t a, int64_t m);
