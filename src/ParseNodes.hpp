#pragma once
#include <string>
#include <memory>
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

class ExprNode {
public:
    auto& getType()
    {
        return type;
    }

private:
    std::variant<LiteralExpr, VariableExpr> type;
};
