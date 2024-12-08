#pragma once

#include "MemoryCell.hpp"
#include "VariableHandler.hpp"
#include <string>
#include <unordered_map>
#include <memory>
#include <vector>

class FunctionDefinition;
/**
 * Class containing all function definitions
 */
class FunctionContainer {
public:
    FunctionContainer(std::shared_ptr<VariableHandler> handler);
    void insertFunction(std::unique_ptr<FunctionDefinition> newFunction);

    MemoryCell getFunction(const std::string& id, const std::vector<MemoryCell>& params) const;

private:
    std::shared_ptr<VariableHandler> _handler;  // Used to update variables
    std::unordered_map<std::string, std::unique_ptr<FunctionDefinition>> _functions;
};
