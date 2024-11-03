#pragma once
#include <unordered_map>
#include <memory>

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
    std::unordered_map<int, std::unique_ptr<MemoryCell>> _memory;
};
