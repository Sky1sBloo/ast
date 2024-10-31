#include "ParseNodes.hpp"

BinaryConditionExpr::BinaryConditionExpr(Types conditionType, ExprNodePtr newExprA, ExprNodePtr newExprB)
    : type(conditionType)
    , exprA(std::move(newExprA))
    , exprB(std::move(newExprB))
{
}

bool BinaryConditionExpr::getCondition()
{
    switch (type) {
    case Types::EQUALS:
        break;
    case Types::GREATER:
        break;
    case Types::LESS:
        break;
    case Types::GREATER_EQUAL:
        break;
    case Types::LESS_EQUAL:
        break;
    }
    return false;
}
