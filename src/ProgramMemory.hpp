#pragma once
#include <queue>
#include <unordered_map>

#include "MemoryCell.hpp"

// Class handling program memory such as variables
class ProgramMemory {
public:
    ProgramMemory();
    /**
     * Allocates a value to the memory
     *
     * @return The address of the memory
     */
    int allocate(const std::string& value);
    int allocate(const MemoryCell& cell);

    /**
     * Deallocates the variable on memory
     */
    void deallocate(int address);

    /**
     * Retrieves the value of address
     *
     * Throws std::out_of_range if address is invalid
     */
    const MemoryCell& retrieve(int address) const;

    /**
     * Sets the value on the adddress pointed
     *
     * Throws std::out_of_range if address is invalid
     */
    void set(int address, const std::string& value);
    void set(int address, const MemoryCell& cell);


private:
    int _highestPtr; // To determine free memory
    std::queue<int> _unusedPtrs;
    std::unordered_map<int, MemoryCell> _memory;
};
