#pragma once
#include "MemoryCell.hpp"
#include <memory>
#include <variant>

/**
 * Base class for all values that can contains value
 */
class ReturnableExpr {
public:
    virtual ~ReturnableExpr() = default;
    virtual const MemoryCell& getValue() = 0;
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
 * Class representing for returning a value from a function
 */
class FunctionReturnExpr : public ReturnableExpr {
public:
    FunctionReturnExpr(std::unique_ptr<ReturnableExpr> value)
        : _value(std::move(value))
    {
    }

    const MemoryCell& getValue() override { return _value->getValue(); }
private:
    std::unique_ptr<ReturnableExpr> _value;
};

/**
 * Class containing both returnable and terminal expr
 */
template <class... ExprVariant>
struct ExprVariantVisitor : ExprVariant... {
    using ExprVariant::operator()...;
};
class Expr {
public:
    Expr(std::unique_ptr<ReturnableExpr> returnableExpr)
        : _expr(std::move(returnableExpr))
    {
    }

    Expr(std::unique_ptr<TerminalExpr> terminalExpr)
        : _expr(std::move(terminalExpr))
    {
    }

    const std::variant<std::unique_ptr<ReturnableExpr>, std::unique_ptr<TerminalExpr>, std::unique_ptr<FunctionReturnExpr>>& getVariant() const { return _expr; }
    template <typename T>
    T& getAs() 
    {
        return *std::get<std::unique_ptr<T>>(_expr);
    }

private:
    std::variant<std::unique_ptr<ReturnableExpr>, std::unique_ptr<TerminalExpr>, std::unique_ptr<FunctionReturnExpr>> _expr;
};

