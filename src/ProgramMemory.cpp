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
        _memory.front().emplace(_highestPtr, value);
        _highestPtr++;
        return _highestPtr - 1;
    } else {
        int currentPtr = _unusedPtrs.front();
        _unusedPtrs.pop();
        _memory.front().emplace(currentPtr, value);
        return currentPtr;
    }
}

int ProgramMemory::allocate(const MemoryCell& cell)
{
    if (_unusedPtrs.empty()) {
        _memory.front().emplace(_highestPtr, cell);
        _highestPtr++;
        return _highestPtr - 1;
    } else {
        int currentPtr = _unusedPtrs.front();
        _unusedPtrs.pop();
        _memory.front().emplace(currentPtr, cell);
        return currentPtr;
    }
}

void ProgramMemory::deallocate(int address)
{
    std::unordered_map<int, MemoryCell>::iterator addressCell = _memory.front().find(address);
    if (addressCell == _memory.front().end()) {
        throw std::out_of_range("ProgramMemory at deallocate: Tried to deallocate unallocated address");
    }
    _memory.front().erase(addressCell);
    _unusedPtrs.push(address);
}

const MemoryCell& ProgramMemory::retrieve(int address) const
{
    for (const auto& memoryStackFrame : _memory) {
        if (memoryStackFrame.contains(address)) {
            return memoryStackFrame.at(address);
        }
    }
    throw std::out_of_range("ProgramMemory at retrieve: Invalid address access");
}

void ProgramMemory::set(int address, const std::string& value)
{
    for (auto& memoryStackFrame : _memory) {
        if (memoryStackFrame.contains(address)) {
            memoryStackFrame.at(address).set(value);
            return;
        }
    }
    throw std::out_of_range("ProgramMemory set: Invalid address access");
}

void ProgramMemory::set(int address, const MemoryCell& cell)
{
    for (auto& memoryStackFrame : _memory) {
        if (memoryStackFrame.contains(address)) {
            memoryStackFrame.at(address) = cell;
            return;
        }
    }
    throw std::out_of_range("ProgramMemory set: Invalid address access");
}

void ProgramMemory::allocateStackFrame()
{
    _memory.emplace_front();
}

void ProgramMemory::deallocateStackFrame()
{
    if (_memory.size() == 0) {
        throw std::out_of_range("Tried to deallocate an empty stack frame");
    }
    _memory.pop_front();
}
