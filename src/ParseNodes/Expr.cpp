#include "BaseParseNodes.hpp"

Expr::Expr(std::unique_ptr<ReturnableExpr> returnableExpr)
    : _expr(std::move(returnableExpr))
{
}

Expr::Expr(std::unique_ptr<TerminalExpr> terminalExpr)
    : _expr(std::move(terminalExpr))
{
}

template <class... ExprVariant>
struct ExprVariantVisitor : ExprVariant... {
    using ExprVariant::operator()...;
};
void Expr::visit(std::function<void(std::unique_ptr<ReturnableExpr>&)> returnableExprFunc,
    std::function<void(std::unique_ptr<TerminalExpr>&)> terminalExprFunc,
    std::function<void(std::unique_ptr<FunctionReturnExpr>&)> functionReturnExprFunc)
{
    std::visit(
        ExprVariantVisitor {
            [returnableExprFunc](std::unique_ptr<ReturnableExpr>& returnableExpr) {
                returnableExprFunc(returnableExpr);
            },
            [terminalExprFunc](std::unique_ptr<TerminalExpr>& terminalExpr) {
                terminalExprFunc(terminalExpr);
            },
            [functionReturnExprFunc](std::unique_ptr<FunctionReturnExpr>& returnableExpr) {
                functionReturnExprFunc(returnableExpr);
            } },
        _expr);
}
