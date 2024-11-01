#pragma once
#include <memory>
#include <string>

#include "DataTypes.hpp"
#include "VariableHandler.hpp"

class ExprNode;
using ExprNodePtr = std::unique_ptr<ExprNode>;

/**
 * Base class for all values that can contains value
 */
class ReturnableExpr {
public:
    virtual ~ReturnableExpr() = default;
    virtual const std::string& getValue() const = 0;
};

/**
 * Base class representing a terminal action
 */
class TerminalExpr {
public:
    virtual ~TerminalExpr() = default;
    virtual void performAction() = 0;
};

/**
 * Node containing constant literals
 */
class LiteralExpr : public ReturnableExpr {
public:
    LiteralExpr(DataType newDataType, const std::string& newValue);
    const std::string& getValue() const override { return value; }

private:
    DataType type;
    const std::string value;
};

/**
 * Node for initialializing variables
 */
class InitializationExpr : public TerminalExpr {
public:
    InitializationExpr(const std::string& varId, std::shared_ptr<VariableHandler> variableHandler);
    InitializationExpr(const std::string& varId, std::unique_ptr<ReturnableExpr> exprNode, std::shared_ptr<VariableHandler> variableHandler);

    void performAction() override;

private:
    const std::string id;
    std::unique_ptr<ReturnableExpr> value;
    std::shared_ptr<VariableHandler> handler;
};

/**
 * Node for assigning values to variables
 */
class AssignExpr : public TerminalExpr {
public:
    AssignExpr(const std::string& varId, std::unique_ptr<ReturnableExpr> exprNode, std::shared_ptr<VariableHandler> variableHandler);

    void performAction() override;
private:
    const std::string id;
    std::unique_ptr<ReturnableExpr> value;
    std::shared_ptr<VariableHandler> handler;
};

