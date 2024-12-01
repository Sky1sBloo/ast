#include "FunctionContainer.hpp"
#include "FunctionDefinition.hpp"
#include <stdexcept>

void FunctionContainer::insertFunction(std::unique_ptr<FunctionDefinition> newFunction)
{
    _functions.emplace(newFunction->getId(), std::move(newFunction));
}

MemoryCell& FunctionContainer::getFunction(const std::string& id, const std::vector<MemoryCell&>& params)
{
    if (!_functions.contains(id)) {
        throw std::invalid_argument("Tried to access unknown function");
    }
};
