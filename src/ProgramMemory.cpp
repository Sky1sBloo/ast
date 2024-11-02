#include "ProgramMemory.hpp"
#include <stdexcept>

ProgramMemory::ProgramMemory()
    : _highestPtr(0)
{
}

int ProgramMemory::allocate(const std::string& value)
{
    _memory.insert({ _highestPtr, value });
    _highestPtr++;
    return _highestPtr - 1;
}

const std::string& ProgramMemory::retrieve(int address)
{
    if (_memory.contains(address)) {
        return _memory[address];
    }
    throw std::out_of_range("ProgramMemory at retrieve: Invalid address access");
}

void ProgramMemory::set(int address, const std::string& value)
{
    if (!_memory.contains(address)) {
        throw std::out_of_range("ProgramMemory set: Invalid address access");
    }

    _memory[address] = value;
}
