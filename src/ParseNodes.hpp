#pragma once
#include <memory>
#include <string>
#include <variant>

class ExprNode;
using ExprNodePtr = std::unique_ptr<ExprNode>;

class LiteralExpr {
public:
    LiteralExpr(const std::string& newValue);

private:
    const std::string value;
};

class VariableExpr {
public:
    VariableExpr(const std::string& id);

private:
    const std::string id;
};

class BinaryConditionExpr {
public:
    enum class Type {
        EQUALS,
        GREATER,
        LESS,
        GREATER_EQUAL,
        LESS_EQUAL
    };

    BinaryConditionExpr(Type conditionType, ExprNodePtr newExprA, ExprNodePtr newExprB);
    bool getCondition();

private:
    ExprNodePtr exprA;
    ExprNodePtr exprB;
    Type type;
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
