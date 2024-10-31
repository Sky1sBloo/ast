#pragma once
#include <variant>
#include <memory>

template <typename T>
class Expr;

template <typename T>
class ConstExpr;

template <typename T>
class ConditionExpr;

template <typename T>
using ExprNode = std::variant<Expr<T>, ConstExpr<T>, ConditionExpr<T>>;



template <typename T>
class Expr {
public:
    virtual ~Expr() {}
    virtual const T& getValue() const;
};

template <typename T>
class ConstExpr {
public:
    ConstExpr(const T& newValue)
        : value(newValue)
    {
    }
    const T& getValue() const override { return value; };

private:
    T value;
};

template <typename T>
class BinaryConditionExpr {
public:
    enum class Types {
        EQUALS,
        GREATER,
        LESS
    };

    BinaryConditionExpr(std::unique_ptr<Expr<T>> newNodeA, std::unique_ptr<Expr<T>> newNodeB);
private:
    std::unique_ptr<Expr<T>> nodeA;
    std::unique_ptr<Expr<T>> nodeB;
};
