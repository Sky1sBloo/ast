#include "ParseNodes.hpp"

InitializationExpr::InitializationExpr(ProgramMemory& programMemory)
{
    programMemory.allocate("");
}

InitializationExpr::InitializationExpr(const std::string& value, ProgramMemory& programMemory)
{
    programMemory.allocate(value);
}
