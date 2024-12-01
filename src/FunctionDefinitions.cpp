#include "FunctionDefinitions.hpp"
#include "ParseNodes.hpp"
#include <stdexcept>

void FunctionDefinitions::insertFunction(std::unique_ptr<FunctionDefinition> newFunction)
{
    _functions.emplace(newFunction->getId(), std::move(newFunction));
}

MemoryCell& FunctionDefinitions::getFunction(const std::string& id, const std::vector<MemoryCell&>& params)
{
    if (!_functions.contains(id)) {
        throw std::invalid_argument("Tried to access unknown function");
    }
};
