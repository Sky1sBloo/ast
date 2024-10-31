#include "ProgramMemory.hpp"

ProgramMemory::ProgramMemory() :
    highestPtr(1),
    memory({{0, "INVALID_ACCESS"}})
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
    return memory[0];
}
