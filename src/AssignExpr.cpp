#include "ParseNodes.hpp"

AssignExpr::AssignExpr(int setAddress, std::unique_ptr<ReturnableExpr> exprNode, std::shared_ptr<ProgramMemory> programMemory)
    : address(setAddress)
    , value(std::move(exprNode))
    , memory(programMemory)
{
}

void AssignExpr::performAction()
{
    memory->set(address, value->getValue());
}
