#pragma once
#include <unordered_map>
#include <string>

// Class handling program memory such as variables
#include <unordered_map>
class ProgramMemory 
{
public:
    ProgramMemory();
    void allocate(const std::string& value);
private:
    int highestPtr;  // To determine free memory
    std::unordered_map<int, std::string> memory;
};
