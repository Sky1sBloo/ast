#pragma once
#include <string>
#include <variant>

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
