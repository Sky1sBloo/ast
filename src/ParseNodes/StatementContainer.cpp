#include "ParseNodes.hpp"

StatementContainer::StatementContainer(std::vector<std::unique_ptr<Expr>> statements)
{
    for (auto& statement : statements) {
        if (std::holds_alternative<std::unique_ptr<ReturnableExpr>>(statement->getVariant())) {
            throw std::invalid_argument("Tried to insert ReturnableExpr in statement container");
        }
        _statements.push_back(std::move(statement));
    }
}

void StatementContainer::performAction()
{
    for (std::unique_ptr<Expr>& statement : _statements) {
        auto& terminalStatement = std::get<std::unique_ptr<TerminalExpr>>(statement->getVariant());
        terminalStatement->performAction();
    }
}

void StatementContainer::insertExpr(std::unique_ptr<Expr> expr)
{
    if (std::holds_alternative<std::unique_ptr<ReturnableExpr>>(expr->getVariant())) {
        throw std::invalid_argument("Tried to insert ReturnableExpr in statement container");
    }
    _statements.push_back(std::move(expr));
}
