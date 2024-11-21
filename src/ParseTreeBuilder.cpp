#include "ParseTreeBuilder.hpp"
#include "ParseNodes.hpp"
#include <ranges>
#include <stdexcept>

ParseTreeBuilder::ParseTreeBuilder(const std::vector<Token>& tokens, std::shared_ptr<VariableHandler> handler)
    : _var_handler(handler)
    , _root()
    , _statementTokens()
{
    getStatementTokens(tokens);

    while (!_statementTokens.empty()) {
        _root.insertExpr(identifyStatement(_statementTokens.front()));
        _statementTokens.pop();
    }

}

void ParseTreeBuilder::getStatementTokens(const std::vector<Token>& tokens)
{
    std::vector<Token> currentStatement;
    for (const Token& token : tokens) {
        if (token.getSubType() == Token::SubTypes::STATEMENT_TERMINATE) {
            _statementTokens.push(currentStatement);
            currentStatement.clear();
            continue;
        }
        currentStatement.push_back(token);
    }
}

std::unique_ptr<TerminalExpr> ParseTreeBuilder::identifyStatement(const std::vector<Token>& statement)
{
    if (statementIsVarInitialization(statement)) {
        const std::string& identifier = statement[1].getValue();
        return std::make_unique<InitializationExpr>(identifier, _var_handler);
    }
    if (statementIsAssignment(statement)) {
        const std::string& identifier = statement[0].getValue();
        const std::string& value = statement[2].getValue();
        return std::make_unique<AssignExpr>(identifier, std::make_unique<LiteralExpr>(value), _var_handler);
    }
    throw std::domain_error("Cannot identify statement");
}

bool ParseTreeBuilder::statementIsVarInitialization(const std::vector<Token>& statement)
{
    if (statement.size() != _varInitializationRuleset.size()) {
        return false;
    }

    for (const auto& [token, expectedToken] : std::views::zip(statement, _varInitializationRuleset)) {
        if (token != expectedToken) {
            return false;
        }
    }
    return true;
}

bool ParseTreeBuilder::statementIsAssignment(const std::vector<Token>& statement)
{
    if (statement.size() != _varAssignmentRuleset.size()) {
        return false;
    }
    for (const auto& [token, expectedToken] : std::views::zip(statement, _varAssignmentRuleset)) {
        if (token != expectedToken) {
            return false;
        }
    }
    return true;
}
