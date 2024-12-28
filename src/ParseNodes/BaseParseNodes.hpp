#pragma once
#include "MemoryCell.hpp"
#include <functional>
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
class FunctionReturnExpr {
public:
    FunctionReturnExpr(std::unique_ptr<ReturnableExpr> value)
        : _value(std::move(value))
    {
    }

    const MemoryCell& getValue() { return _value->getValue(); }
private:
    std::unique_ptr<ReturnableExpr> _value;
};

/**
 * Class containing both returnable and terminal expr
 */
class Expr {
public:
    Expr(std::unique_ptr<ReturnableExpr> returnableExpr);

    Expr(std::unique_ptr<TerminalExpr> terminalExpr);

    const std::variant<std::unique_ptr<ReturnableExpr>, std::unique_ptr<TerminalExpr>, std::unique_ptr<FunctionReturnExpr>>& getVariant() const { return _expr; }
    template <typename T>
    T& getAs() 
    {
        return *std::get<std::unique_ptr<T>>(_expr);
    }

    /**
     * Function for visiting the variant
     *
     * @param returnableExprFunc Function for handling returnable expressions
     * @param terminalExprFunc Function for handling terminal expressions
     * @param functionReturnExprFunc Function for handling function return expressions
    */
    void visit(std::function<void(std::unique_ptr<ReturnableExpr>&)> returnableExprFunc, 
               std::function<void(std::unique_ptr<TerminalExpr>&)> terminalExprFunc, 
               std::function<void(std::unique_ptr<FunctionReturnExpr>&)> functionReturnExprFunc);

private:
    std::variant<std::unique_ptr<ReturnableExpr>, std::unique_ptr<TerminalExpr>, std::unique_ptr<FunctionReturnExpr>> _expr;
};

