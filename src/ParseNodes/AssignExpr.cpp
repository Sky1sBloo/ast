#include "ParseNodes.hpp"

AssignExpr::AssignExpr(const std::string& id, std::unique_ptr<ReturnableExpr> value, std::shared_ptr<VariableHandler> handler)
    : _id(id)
    , _value(std::move(value))
    , _handler(handler)
{
}

void AssignExpr::performAction()
{
    _handler->setValue(_id, _value->getValue());
}
