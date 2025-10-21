#pragma once

#include <iostream>
#include <windows.h>
#include <memory>

/**
 * @brief Represents the core memory storage and aging logic.
 */
class MemoryStore {
public:
    MemoryStore();
    ~MemoryStore();

    void access_data(int key);
    void print_status();

private:
    CRITICAL_SECTION data_mutex;
    // Add other member variables here (e.g., data structures for aging)
};