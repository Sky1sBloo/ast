#pragma once
#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>

#include "BaseParseNodes.hpp"

// Class for handling function parameters
class FunctionParameterContainer {
public:
    FunctionParameterContainer() : _params()
    {
    }

    void addParam(const std::string& id, std::unique_ptr<ReturnableExpr> expr)
    {
        _params.insert({ id, std::move(expr) });
    }

    const MemoryCell& getParam(const std::string& id) const
    {
        if (!_params.contains(id)) {
            throw std::invalid_argument("Param name doesn't exist");
        }
        return _params.at(id)->getValue();
    }

private:
    std::unordered_map<std::string, std::unique_ptr<ReturnableExpr>> _params;
};
