#include "ParseNodes.hpp"

StatementContainer::StatementContainer(std::vector<std::unique_ptr<TerminalExpr>> statements)
{
    for (auto& statement : statements) {
        _statements.push_back(std::move(statement));
    }
}

void StatementContainer::performAction()
{
    for (auto& statement : _statements) {
        statement->performAction();
    }
}

void StatementContainer::insertExpr(std::unique_ptr<TerminalExpr> expr)
{
    _statements.push_back(std::move(expr));
}
