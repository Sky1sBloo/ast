#pragma once
#include <memory>
#include <string>
#include <variant>
#include <vector>

#include "MemoryCell.hpp"
#include "VariableHandler.hpp"

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

class StatementContainer : public TerminalExpr {
public:
    StatementContainer()
        : _statements()
    {
    }
    StatementContainer(std::vector<std::unique_ptr<Expr>> statements);
    void performAction() override;
    void insertExpr(std::unique_ptr<Expr> expr);

private:
    std::vector<std::unique_ptr<Expr>> _statements;
};

/**
 * Node containing constant literals
 */
class LiteralExpr : public ReturnableExpr {
public:
    LiteralExpr(const std::string& value);
    const MemoryCell& getValue() const override { return _value; }

private:
    const MemoryCell _value;
};

/**
 * Node for initialializing variables
 */
class InitializationExpr : public TerminalExpr {
public:
    InitializationExpr(const std::string& id, std::shared_ptr<VariableHandler> handler);
    InitializationExpr(const std::string& id, std::unique_ptr<ReturnableExpr> value, std::shared_ptr<VariableHandler> handler);

    void performAction() override;

private:
    const std::string _id;
    std::unique_ptr<ReturnableExpr> _value;
    std::shared_ptr<VariableHandler> _handler;
};

/**
 * Node for assigning values to variables
 */
class AssignExpr : public TerminalExpr {
public:
    AssignExpr(const std::string& id, std::unique_ptr<ReturnableExpr> value, std::shared_ptr<VariableHandler> handler);

    void performAction() override;

private:
    const std::string _id;
    std::unique_ptr<ReturnableExpr> _value;
    std::shared_ptr<VariableHandler> _handler;
};

template <class... ExprVariant>
struct ExprVariantVisitor : ExprVariant... {
    using ExprVariant::operator()...;
};
class FunctionExpr : public ReturnableExpr {
public:
    FunctionExpr(const std::string& id, std::vector<std::unique_ptr<Expr>>& statements);

    const MemoryCell& getValue() const override;

private:
    const std::string _id;
    std::vector<std::unique_ptr<Expr>>& _statements;
};
