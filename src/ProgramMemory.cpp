#include "ProgramMemory.hpp"
#include <stdexcept>
#include <unordered_map>

ProgramMemory::ProgramMemory()
    : _highestPtr(0)
    , _unusedPtrs()
{
}

int ProgramMemory::allocate(const std::string& value)
{
    if (_unusedPtrs.empty()) {
        _memory.emplace(_highestPtr, value);
        _highestPtr++;
        return _highestPtr - 1;
    } else {
        int currentPtr = _unusedPtrs.front();
        _unusedPtrs.pop();
        _memory.emplace(currentPtr, value);
        return currentPtr;
    }
}

int ProgramMemory::allocate(const MemoryCell& cell)
{
    if (_unusedPtrs.empty()) {
        _memory.emplace(_highestPtr, cell);
        _highestPtr++;
        return _highestPtr - 1;
    } else {
        int currentPtr = _unusedPtrs.front();
        _unusedPtrs.pop();
        _memory.emplace(currentPtr, cell);
        return currentPtr;
    }
}

void ProgramMemory::deallocate(int address)
{
    std::unordered_map<int, MemoryCell>::iterator addressCell = _memory.find(address);
    if (addressCell == _memory.end()) {
        throw std::out_of_range("ProgramMemory at deallocate: Tried to deallocate unallocated address");
    }
    _memory.erase(addressCell);
    _unusedPtrs.push(address);
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
