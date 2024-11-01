#pragma once
#include <memory>
#include <string>
#include <variant>

#include "DataTypes.hpp"
#include "ProgramMemory.hpp"

class ExprNode;
using ExprNodePtr = std::unique_ptr<ExprNode>;

class LiteralExpr {
public:
    LiteralExpr(DataType newDataType, const std::string& newValue);

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
    InitializationExpr(const std::string& value, ProgramMemory& programMemory);
};

/**
 * Node for assigning values to variables
 */
class AssignExpr {
public:
private:
};

class BinaryConditionExpr {
public:
    enum class Types {
        EQUALS,
        GREATER,
        LESS,
        GREATER_EQUAL,
        LESS_EQUAL
    };

    BinaryConditionExpr(Types conditionType, ExprNodePtr newExprA, ExprNodePtr newExprB);
    bool getCondition();

private:
    Types type;
    ExprNodePtr exprA;
    ExprNodePtr exprB;
};

class ExprNode {
public:
    auto& getType()
    {
        return type;
    }

private:
    std::variant<LiteralExpr, InitializationExpr> type;
};
