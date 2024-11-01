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
    InitializationExpr(std::shared_ptr<ProgramMemory> programMemory);
    InitializationExpr(std::unique_ptr<ReturnableExpr> exprNode, std::shared_ptr<ProgramMemory> programMemory);

    void performAction() override;

private:
    std::unique_ptr<ReturnableExpr> value;
    std::shared_ptr<ProgramMemory> memory;
};

/**
 * Node for assigning values to variables
 */
class AssignExpr : public TerminalExpr {
public:
    AssignExpr(int setAddress, std::unique_ptr<ReturnableExpr> exprNode, std::shared_ptr<ProgramMemory> programMemory);

    void performAction() override;
private:
    int address;
    std::unique_ptr<ReturnableExpr> value;
    std::shared_ptr<ProgramMemory> memory;
};

