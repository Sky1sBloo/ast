#pragma once
#include "ParseNodes.hpp"
#include <stdexcept>
#include <unordered_map>

// Class for handling function parameters
class FunctionParameterContainer {
public:
    FunctionParameterContainer(std::initializer_list<std::pair<const std::string, std::unique_ptr<ReturnableExpr>>> params)
        : _params(params)
    {
    }

    void addParam(const std::string& id, std::unique_ptr<ReturnableExpr> expr)
    {
        _params.insert({id, std::move(expr)});
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
/**
 * Node for returnable functions
 */
class FunctionExpr : public ReturnableExpr {
public:
    FunctionExpr(const std::string& id, std::shared_ptr<VariableHandler> handler, std::unique_ptr<FunctionParameterContainer> params);
    void insertExpr(std::unique_ptr<Expr> expr);

    const MemoryCell& getValue() const override;

private:
    const std::string _id;
    std::vector<std::unique_ptr<Expr>> _statements;
    std::unique_ptr<FunctionParameterContainer> _params;
    std::shared_ptr<VariableHandler> _handler;
};

/**
 * Node for non returnable functions
 */
class TerminalFunctionExpr : public TerminalExpr {
public:
    TerminalFunctionExpr(const std::string& id);
    void insertExpr(std::unique_ptr<Expr> expr);
    void performAction() override;

private:
    const std::string _id;
    std::vector<std::unique_ptr<Expr>> _statements;
};
