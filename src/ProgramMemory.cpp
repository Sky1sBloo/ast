#include "ProgramMemory.hpp"
#include <stdexcept>

ProgramMemory::ProgramMemory()
    : _highestPtr(0)
{
}

int ProgramMemory::allocate(const std::string& value)
{
    _memory.emplace(_highestPtr, value);
    _highestPtr++;
    return _highestPtr - 1;
}

int ProgramMemory::allocate(const MemoryCell& cell)
{
    _memory.emplace(_highestPtr, cell);
    _highestPtr++;
    return _highestPtr - 1;
}

const MemoryCell& ProgramMemory::retrieve(int address) const
{
    if (_memory.contains(address)) {
        return _memory.at(address);
    }
    throw std::out_of_range("ProgramMemory at retrieve: Invalid address access");
}

void ProgramMemory::set(int address, const std::string& value)
{
    if (!_memory.contains(address)) {
        throw std::out_of_range("ProgramMemory set: Invalid address access");
    }

    _memory.at(address).set(value);
}

void ProgramMemory::set(int address, const MemoryCell& cell)
{
    if (!_memory.contains(address)) {
        throw std::out_of_range("ProgramMemory set: Invalid address access");
    }

    _memory.at(address) = cell;
}
