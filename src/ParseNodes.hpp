#pragma once
#include <string>

class LiteralExpr {
    LiteralExpr(const std::string& newValue);
private:
    const std::string value;
};

class VariableExpr {
    VariableExpr(const std::string& id);
private:
    const std::string id;
};
