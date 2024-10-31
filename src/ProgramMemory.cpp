#include "ProgramMemory.hpp"

ProgramMemory::ProgramMemory() :
    highestPtr(0)
{
}

void ProgramMemory::allocate(const std::string& value)
{
    memory.insert({highestPtr, value});
    highestPtr++;
}
