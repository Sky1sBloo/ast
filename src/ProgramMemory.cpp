#include "ProgramMemory.hpp"
#include <stdexcept>
#include <unordered_map>

ProgramMemory::ProgramMemory()
    : _highestPtr(0)
    , _unusedPtrs()
{
    allocateStackFrame();
}

int ProgramMemory::allocate(const std::string& value)
{
    if (_unusedPtrs.empty()) {
        _memory.back().emplace(_highestPtr, value);
        _highestPtr++;
        return _highestPtr - 1;
    } else {
        int currentPtr = _unusedPtrs.front();
        _unusedPtrs.pop();
        _memory.back().emplace(currentPtr, value);
        return currentPtr;
    }
}

int ProgramMemory::allocate(const MemoryCell& cell)
{
    if (_unusedPtrs.empty()) {
        _memory.back().emplace(_highestPtr, cell);
        _highestPtr++;
        return _highestPtr - 1;
    } else {
        int currentPtr = _unusedPtrs.front();
        _unusedPtrs.pop();
        _memory.back().emplace(currentPtr, cell);
        return currentPtr;
    }
}

void ProgramMemory::deallocate(int address)
{
    std::unordered_map<int, MemoryCell>::iterator addressCell = _memory.back().find(address);
    if (addressCell == _memory.back().end()) {
        throw std::out_of_range("ProgramMemory at deallocate: Tried to deallocate unallocated address");
    }
    _memory.back().erase(addressCell);
    _unusedPtrs.push(address);
}

const MemoryCell& ProgramMemory::retrieve(int address) const
{
    for (auto it = _memory.rbegin(); it != _memory.rend(); it++) {
        if ((*it).contains(address)) {
            return (*it).at(address);
        }
    }
    throw std::out_of_range("ProgramMemory at retrieve: Invalid address access");
}

void ProgramMemory::set(int address, const std::string& value)
{
    for (auto it = _memory.rbegin(); it != _memory.rend(); it++) {
        if ((*it).contains(address)) {
            (*it).at(address).set(value);
            return;
        }
    }
    throw std::out_of_range("ProgramMemory set: Invalid address access");
}

void ProgramMemory::set(int address, const MemoryCell& cell)
{
    for (auto it = _memory.rbegin(); it != _memory.rend(); it++) {
        if ((*it).contains(address)) {
            (*it).at(address) = cell;
            return;
        }
    }
    throw std::out_of_range("ProgramMemory set: Invalid address access");
}

void ProgramMemory::allocateStackFrame()
{
    _memory.emplace_back();
}

void ProgramMemory::deallocateStackFrame()
{
    if (_memory.size() == 0) {
        throw std::out_of_range("Tried to deallocate an empty stack frame");
    }
    _memory.pop_back();
}
