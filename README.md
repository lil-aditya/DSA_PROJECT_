
# ADIPE - Algorithmic Data Integrity and Prioritization Engine (Toy Demo)
This archive contains a self-contained C++ command-line demo implementing the ADIPE roadmap: simple RSA-based signatures (toy primes), fast modular exponentiation, a simple hash/checksum, an O(1) metadata map (unordered_map wrapper), a priority engine using std::priority_queue, and a graph routing demo (BFS).

## Build
```
make
./build/ADIPE
```

## Notes
- This is a demonstration / educational implementation. For production cryptography, use established libraries (OpenSSL, libsodium, GMP).
- Key generation uses small fixed primes for simplicity so the demo runs without big-integer libraries.
