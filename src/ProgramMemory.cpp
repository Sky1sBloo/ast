#include "ProgramMemory.hpp"
#include <stdexcept>

ProgramMemory::ProgramMemory() :
    highestPtr(0)
{
}

int ProgramMemory::allocate(const std::string& value)
{
    memory.insert({highestPtr, value});
    highestPtr++;
    return highestPtr - 1;
}


const std::string& ProgramMemory::retrieve(int address)
{
    if (memory.contains(address)) {
        return memory[address];
    }
    throw std::out_of_range("Invalid address access");
}
