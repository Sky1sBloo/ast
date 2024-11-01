#include "ParseNodes.hpp"

VariableExpr::VariableExpr(const std::string& newId, std::shared_ptr<ProgramMemory> programMemory)
    : id(newId)
    , memoryAddress(-1)
    , memory(programMemory)
{
}

VariableExpr::VariableExpr(const std::string& newId, const std::string& value, std::shared_ptr<ProgramMemory> programMemory)
    : id(newId)
    , memoryAddress(programMemory->allocate(value))
    , memory(programMemory)
{
}

void VariableExpr::setValue(const std::string& newValue)
{
    memory->set(memoryAddress, newValue);
}
