#pragma once

#include "MemoryCell.hpp"
#include <string>
#include <unordered_map>
#include <memory>
#include <vector>

class FunctionDefinition;
/**
 * Class containing all function definitions
 */
class FunctionDefinitions {
public:
    void insertFunction(std::unique_ptr<FunctionDefinition> newFunction);

    MemoryCell& getFunction(const std::string& id, const std::vector<MemoryCell&>& params);

private:
    std::unordered_map<std::string, std::unique_ptr<FunctionDefinition>> _functions;
};
