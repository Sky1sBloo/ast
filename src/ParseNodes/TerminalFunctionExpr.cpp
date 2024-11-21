#include "ParseNodes.hpp"

TerminalFunctionExpr::TerminalFunctionExpr(const std::string& id)
    : _id(id)
    , _statements()
{
}

void TerminalFunctionExpr::insertExpr(std::unique_ptr<Expr> expr)
{
    _statements.push_back(std::move(expr));
}

void TerminalFunctionExpr::performAction()
{
    const MemoryCell* returnable = nullptr;
    for (auto& statement : _statements) {
        std::visit(
            ExprVariantVisitor {
                [](const std::unique_ptr<TerminalExpr>& terminalExpr) {
                    terminalExpr->performAction();
                },
                [](const std::unique_ptr<ReturnableExpr>& returnableExpr) {
                    throw std::runtime_error("Terminal Function Expression has returnable expression");
                } },
            statement->getVariant());
    }
}
