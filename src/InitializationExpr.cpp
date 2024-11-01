#include "ParseNodes.hpp"

InitializationExpr::InitializationExpr(ProgramMemory& programMemory)
{
    programMemory.allocate("");
}

InitializationExpr::InitializationExpr(std::unique_ptr<ReturnableExpr> exprNode, ProgramMemory& programMemory) :
    value(std::move(exprNode))
{
    programMemory.allocate(value->getValue());
}
