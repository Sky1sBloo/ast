#include "ParseNodes.hpp"

template <typename T>
BinaryConditionExpr<T>::BinaryConditionExpr(std::unique_ptr<Expr<T>> newNodeA, std::unique_ptr<Expr<T>> newNodeB)
    : nodeA(std::move(newNodeA))
    , nodeB(std::move(newNodeB))
{
}

