#pragma once
#include <memory>
#include <string>
#include <vector>

#include "BaseParseNodes.hpp"
#include "FunctionContainer.hpp"
#include "MemoryCell.hpp"
#include "VariableHandler.hpp"

/**
 * Node containing constant literals
 */
class LiteralExpr : public ReturnableExpr {
public:
    LiteralExpr(const std::string& value);
    const MemoryCell& getValue() override { return _value; }

private:
    const MemoryCell _value;
};

class VariableIdentifier : public ReturnableExpr {
public:
    VariableIdentifier(const std::string& id, std::shared_ptr<VariableHandler> handler)
        : _id(id)
        , _handler(handler)
    {
    }

    const MemoryCell& getValue() override { return _handler->getValue(_id); }

private:
    const std::string _id;
    std::shared_ptr<VariableHandler> _handler;
};
/**
 * Node for initialializing variables
 */
class InitializationExpr : public TerminalExpr {
public:
    InitializationExpr(const std::string& id, std::shared_ptr<VariableHandler> handler);
    InitializationExpr(const std::string& id, std::unique_ptr<ReturnableExpr> value, std::shared_ptr<VariableHandler> handler);

    void performAction() override;

private:
    const std::string _id;
    std::unique_ptr<ReturnableExpr> _value;
    std::shared_ptr<VariableHandler> _handler;
};

/**
 * Node for assigning values to variables
 */
class AssignExpr : public TerminalExpr {
public:
    AssignExpr(const std::string& id, std::unique_ptr<ReturnableExpr> value, std::shared_ptr<VariableHandler> handler);

    void performAction() override;

private:
    const std::string _id;
    std::unique_ptr<ReturnableExpr> _value;
    std::shared_ptr<VariableHandler> _handler;
};

/**
 * Node for calling functions
 */
class FunctionCallExpr : public ReturnableExpr {
public:
    FunctionCallExpr(const std::string& id, std::shared_ptr<FunctionContainer> functionDefinitions, std::shared_ptr<VariableHandler> handler);

    /**
     * Param is inserted by order
     */
    void insertParam(std::unique_ptr<ReturnableExpr> param);

    const MemoryCell& getValue() override;

private:
    std::string _id;
    std::vector<std::unique_ptr<ReturnableExpr>> _params;
    std::shared_ptr<FunctionContainer> _functionDefinitions;
    std::shared_ptr<VariableHandler> _handler;

    MemoryCell _value;  // Since it needs to take ownership
};

/**
 * Node for non named returnable functions
 */
class StatementContainer : public TerminalExpr {
public:
    StatementContainer()
        : _statements()
    {
    }

    void performAction() override;
    void insertExpr(std::unique_ptr<Expr> expr);

private:
    std::vector<std::unique_ptr<Expr>> _statements;
};
