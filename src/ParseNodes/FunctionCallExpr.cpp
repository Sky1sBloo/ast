#include "ParseNodes.hpp"

FunctionCallExpr::FunctionCallExpr(const std::string& id, std::shared_ptr<FunctionContainer> functionDefinitions, std::shared_ptr<VariableHandler> handler)
    : _id(id)
    , _functionDefinitions(functionDefinitions)
    , _params()
    , _handler(handler)
{
}

void FunctionCallExpr::insertParam(std::unique_ptr<ReturnableExpr> param)
{
    _params.push_back(std::move(param));
}

const MemoryCell& FunctionCallExpr::getValue() const
{
    std::vector<MemoryCell> paramValues;
    paramValues.reserve(_params.size());

    for (const auto& param : _params) {
        paramValues.push_back(param->getValue());
    }

    return _functionDefinitions->getFunction(_id, paramValues);
}
