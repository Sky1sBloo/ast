#include "ParseNodes.hpp"

AssignExpr::AssignExpr(const std::string& varId, std::unique_ptr<ReturnableExpr> exprNode, std::shared_ptr<VariableHandler> variableHandler)
    : id(varId)
    , value(std::move(exprNode))
    , handler(variableHandler)
{
}

void AssignExpr::performAction()
{
    handler->setValue(id, value->getValue());
}
