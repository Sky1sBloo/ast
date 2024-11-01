#include "ParseNodes.hpp"

InitializationExpr::InitializationExpr(const std::string& newId, std::shared_ptr<ProgramMemory> programMemory)
    : id(newId)
    , memoryAddress(programMemory->allocate(""))
    , memory(programMemory)
{
}

InitializationExpr::InitializationExpr(const std::string& newId, const std::string& value, std::shared_ptr<ProgramMemory> programMemory)
    : id(newId)
    , memoryAddress(programMemory->allocate(value))
    , memory(programMemory)
{
}

