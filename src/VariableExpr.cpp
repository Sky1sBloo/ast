#include "ParseNodes.hpp"

    VariableExpr(const std::string& newId, std::shared_ptr<ProgramMemory> programMemory);
VariableExpr::VariableExpr(const std::string& newId)
    : id(newId)
    , memoryAddress(-1)
{
}

VariableExpr::VariableExpr(const std::string& newId, const std::string& value, ProgramMemory& memory)
    : id(newId)
    , memoryAddress(memory.allocate(value))
{
}
