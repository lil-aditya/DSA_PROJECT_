#include "MemoryStore.hpp"

MemoryStore::MemoryStore() {
    InitializeCriticalSection(&data_mutex);
}

MemoryStore::~MemoryStore() {
    DeleteCriticalSection(&data_mutex);
}

void MemoryStore::access_data(int key) {
    EnterCriticalSection(&data_mutex);
    // Your code here
    LeaveCriticalSection(&data_mutex);
}

void MemoryStore::print_status() {
    EnterCriticalSection(&data_mutex);
    // Your code here
    LeaveCriticalSection(&data_mutex);
}