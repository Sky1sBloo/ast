#include "ParseNodes.hpp"

StatementContainer::StatementContainer(std::unique_ptr<std::vector<TerminalExpr>> statements)
    : _statements(std::move(statements))
{
}

void StatementContainer::performAction()
{
    for (TerminalExpr& statement : *_statements) {
        statement.performAction();
    }
}
