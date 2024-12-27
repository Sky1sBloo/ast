#include "RulesetExpr.hpp"

RulesetExpr::RulesetExpr(std::unique_ptr<Expr> expr)
    : _variant(std::move(expr))
    , _type(Types::EXPR)
{
}

RulesetExpr::RulesetExpr(std::unique_ptr<FunctionDefinition> functionDefinition)
    : _variant(std::move(functionDefinition))
    , _type(Types::FUNCTION_DEFINITION)
{
}

RulesetExpr::RulesetExpr(Types type)
    : _type(type)
{
    if (type != Types::FUNCTION_TERMINATION) {
        throw std::invalid_argument("Invalid type for function termination");
    }
}

RulesetExpr::RulesetExpr()
    : _variant(std::monostate())
    , _type(Types::INVALID)
{
}

void RulesetExpr::visit(std::function<void(std::unique_ptr<Expr>&)> exprVisitor,
    std::function<void(std::unique_ptr<FunctionDefinition>&)> functionVisitor,
    std::function<void()> terminationVisitor, std::function<void()> noneVisitor)
{
    switch (_type) {
    case Types::EXPR:
        exprVisitor(std::get<std::unique_ptr<Expr>>(_variant));
        break;
    case Types::FUNCTION_DEFINITION:
        functionVisitor(std::get<std::unique_ptr<FunctionDefinition>>(_variant));
        break;
    case Types::FUNCTION_TERMINATION:
        terminationVisitor();
        break;
    case Types::INVALID:
        noneVisitor();
        break;
    }
}
