#include "ParseNodes.hpp"
InitializationExpr::InitializationExpr(const std::string& varId, std::shared_ptr<VariableHandler> variableHandler)
    : id(varId)
    , value(nullptr)
    , handler(variableHandler)
{
}

InitializationExpr::InitializationExpr(const std::string& varId, std::unique_ptr<ReturnableExpr> exprNode, std::shared_ptr<VariableHandler> variableHandler)
    : id(varId)
    , value(std::move(exprNode))
    , handler(variableHandler)
{
}

void InitializationExpr::performAction()
{
    if (value) {
        handler->allocate(id, value->getValue());
    } else {
        handler->allocate(id);
    }
}
