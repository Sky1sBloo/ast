#include "ParseNodes.hpp"

InitializationExpr::InitializationExpr(std::shared_ptr<ProgramMemory> programMemory)
    : memoryAddress(programMemory->allocate(""))
    , memory(programMemory)
{
}

InitializationExpr::InitializationExpr(const std::string& value, std::shared_ptr<ProgramMemory> programMemory)
    : memoryAddress(programMemory->allocate(value))
    , memory(programMemory)
{
}
