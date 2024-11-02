#pragma once
#include <string>
#include <unordered_map>

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

    /**
     * Retrieves the value of address
     *
     * Throws std::out_of_range if address is invalid
     */
    const std::string& retrieve(int address);

    /**
     * Sets the value on the adddress pointed
     *
     * Throws std::out_of_range if address is invalid
     */
    void set(int address, const std::string& value);

private:
    int _highestPtr; // To determine free memory
    std::unordered_map<int, std::string> _memory;
};
