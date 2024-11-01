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

class VariableInitializationExpr {
public:
    VariableInitializationExpr(const std::string& newId, std::shared_ptr<ProgramMemory> programMemory);
    VariableInitializationExpr(const std::string& newId, const std::string& value, std::shared_ptr<ProgramMemory> programMemory);
private:
    const std::string id;
    int memoryAddress; // -1 if unallocated
    std::shared_ptr<ProgramMemory> memory;
};

/**
 * Node for assigning values to variables
 */
class AssignExpr {
public:
    AssignExpr(std::shared_ptr<VariableExpr> toAssign, ExprNodePtr value);

private:
    std::shared_ptr<VariableExpr> expr;
    ExprNodePtr value;
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
