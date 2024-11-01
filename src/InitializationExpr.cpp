#include "ParseNodes.hpp"

InitializationExpr::InitializationExpr(std::shared_ptr<ProgramMemory> programMemory)
{
    programMemory->allocate("");
}

InitializationExpr::InitializationExpr(const std::string& value, std::shared_ptr<ProgramMemory> programMemory)
{
    programMemory->allocate(value);
}
