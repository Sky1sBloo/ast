#include "ParseNodes.hpp"

InitializationExpr::InitializationExpr(const std::string& id, std::shared_ptr<VariableHandler> handler)
    : _id(id)
    , _value(nullptr)
    , _handler(handler)
{
}

InitializationExpr::InitializationExpr(const std::string& id, std::unique_ptr<ReturnableExpr> value, std::shared_ptr<VariableHandler> handler)
    : _id(id)
    , _value(std::move(value))
    , _handler(handler)
{
}

void InitializationExpr::performAction()
{
    if (_value) {
        _handler->allocate(_id, _value->getValue());
    } else {
        _handler->allocate(_id);
    }
}
