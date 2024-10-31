#pragma once
#include <memory>
#include <string>
#include <variant>
#include "DataTypes.hpp"

class ExprNode;
using ExprNodePtr = std::unique_ptr<ExprNode>;

class LiteralExpr {
public:
    LiteralExpr(DataType newDataType, const std::string& newValue);

private:
    DataType type;
    const std::string value;
};

class VariableExpr {
public:
    VariableExpr(const std::string& id);

private:
    const std::string id;
    int memoryAddress;
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
    std::variant<LiteralExpr, VariableExpr> type;
};
