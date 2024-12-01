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
    virtual const MemoryCell& getValue() const = 0;
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

    const std::variant<std::unique_ptr<ReturnableExpr>, std::unique_ptr<TerminalExpr>>& getVariant() const { return _expr; }
    template <typename T>
    const T& getAs() const
    {
        return *std::get<std::unique_ptr<T>>(_expr);
    }

private:
    std::variant<std::unique_ptr<ReturnableExpr>, std::unique_ptr<TerminalExpr>> _expr;
};

