#pragma once
#include <memory>
#include <string>

#include "DataTypes.hpp"
#include "ProgramMemory.hpp"

class ExprNode;
using ExprNodePtr = std::unique_ptr<ExprNode>;

/**
 * Base class for all values that can contains value
 */
class ReturnableExpr {
public:
    virtual ~ReturnableExpr() = 0;
    virtual const std::string& getValue() const = 0;
};

/**
 * Base class representing a terminal action
 */
class TerminalExpr {
public:
    virtual ~TerminalExpr() = 0;
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
class InitializationExpr {
public:
    InitializationExpr(ProgramMemory& programMemory);
    InitializationExpr(std::unique_ptr<ReturnableExpr> exprNode, ProgramMemory& programMemory);

private:
    std::unique_ptr<ReturnableExpr> value;
};

/**
 * Node for assigning values to variables
 */
class AssignExpr {
public:
private:
};

class BinaryConditionExpr : public ReturnableExpr {
public:
    enum class Types {
        EQUALS,
        GREATER,
        LESS,
        GREATER_EQUAL,
        LESS_EQUAL
    };

    BinaryConditionExpr(Types conditionType, std::unique_ptr<ReturnableExpr> newExprA, std::unique_ptr<ReturnableExpr> newExprB);
    bool getCondition();

    const std::string& getValue() const override { return answer; }

private:
    Types type;
    std::unique_ptr<ReturnableExpr> exprA;
    std::unique_ptr<ReturnableExpr> exprB;
    std::string answer = "BinaryCondition";
};
