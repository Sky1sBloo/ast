#include "FunctionContainer.hpp"
#include "FunctionDefinition.hpp"
#include <ranges>
#include <stdexcept>

FunctionContainer::FunctionContainer(std::shared_ptr<VariableHandler> handler)
    : _handler(handler)
{
}

void FunctionContainer::insertFunction(std::unique_ptr<FunctionDefinition> newFunction)
{
    _functions.emplace(newFunction->getId(), std::move(newFunction));
}

const MemoryCell& FunctionContainer::getFunction(const std::string& id, const std::vector<MemoryCell>& params) const
{
    if (!_functions.contains(id)) {
        throw std::invalid_argument("Tried to access unknown function");
    }
    FunctionDefinition& func = *_functions.at(id);
    if (func.getParams().size() != params.size()) {
        throw std::invalid_argument("Parameter of function doesn't match definition");
    }
    for (const auto& [paramId, value] : std::ranges::views::zip(func.getParams(), params)) {
        _handler->setValue(paramId, value);
    }
    return func.getValue();
};
