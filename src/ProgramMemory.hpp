#pragma once
#include <unordered_map>
#include <string>

// Class handling program memory such as variables
class ProgramMemory 
{
public:
    ProgramMemory();
    void allocate(const std::string& value);
    const std::string& retrieve(int address);
private:
    int highestPtr;  // To determine free memory
    std::unordered_map<int, std::string> memory;
};
