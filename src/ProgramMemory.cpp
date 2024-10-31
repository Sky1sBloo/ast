#include "ProgramMemory.hpp"

ProgramMemory::ProgramMemory() :
    highestPtr(1),
    memory({{0, "INVALID_ACCESS"}})
{
}

void ProgramMemory::allocate(const std::string& value)
{
    memory.insert({highestPtr, value});
    highestPtr++;
}


const std::string& ProgramMemory::retrieve(int address)
{
    if (memory.contains(address)) {
        return memory[address];
    }
    return memory[0];
}
