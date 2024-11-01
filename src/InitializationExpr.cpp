#include "ParseNodes.hpp"

InitializationExpr::InitializationExpr(std::shared_ptr<ProgramMemory> programMemory)
    : value(nullptr)
    , memory(programMemory)
{
}

InitializationExpr::InitializationExpr(std::unique_ptr<ReturnableExpr> exprNode, std::shared_ptr<ProgramMemory> programMemory)
    : value(std::move(exprNode))
    , memory(programMemory)
{
}

void InitializationExpr::performAction()
{
    memory->allocate(value ? value->getValue() : "");
}
