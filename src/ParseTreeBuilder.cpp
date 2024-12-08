#include "ParseTreeBuilder.hpp"
#include "FunctionDefinition.hpp"
#include "ParseNodes.hpp"
#include <optional>
#include <ranges>
#include <stdexcept>

ParseTreeBuilder::ParseTreeBuilder(const std::vector<Token>& tokens, std::shared_ptr<VariableHandler> handler, std::shared_ptr<FunctionContainer> funcContainer)
    : _var_handler(handler)
    , _func_container(funcContainer)
    , _root()
    , _statementTokens()
{
    getStatementTokens(tokens);

    while (!_statementTokens.empty()) {
        auto expr = identifyStatement(_statementTokens.front());
        if (expr.has_value()) {
            _root.insertExpr(std::move(expr.value()));
        }
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

std::optional<std::unique_ptr<Expr>> ParseTreeBuilder::identifyStatement(const std::vector<Token>& statement)
{
    if (statementMatchesRuleset(statement, _varInitializationRuleset)) {
        const std::string& identifier = statement[1].getValue();
        auto initializationExpr = std::make_unique<InitializationExpr>(identifier, _var_handler);
        return std::make_unique<Expr>(std::move(initializationExpr));
    }
    if (statementMatchesRuleset(statement, _varAssignmentRuleset)) {
        const std::string& identifier = statement[0].getValue();
        const std::string& value = statement[2].getValue();
        auto assignExpr = std::make_unique<AssignExpr>(identifier, std::make_unique<LiteralExpr>(value), _var_handler);
        return std::make_unique<Expr>(std::move(assignExpr));
    }
    if (statementMatchesRuleset(statement, _varInitializationAndAssignmentRuleset)) {
        const std::string& identifier = statement[1].getValue();
        const std::string& value = statement[3].getValue();
        auto initializationExpr = std::make_unique<InitializationExpr>(identifier, std::make_unique<LiteralExpr>(value), _var_handler);
        return std::make_unique<Expr>(std::move(initializationExpr));
    }
    if (statementMatchesRuleset(statement, _functionDefinitionRuleset)) {
        const std::string& identifier = statement[1].getValue();
        _func_container->insertFunction(std::make_unique<FunctionDefinition>(identifier, _var_handler));
        return std::nullopt;
    }
    throw std::domain_error("Cannot identify statement");
}

bool ParseTreeBuilder::statementMatchesRuleset(const std::vector<Token>& statement, std::span<const Token> ruleset)
{
    if (statement.size() != ruleset.size()) {
        return false;
    }

    for (const auto& [token, expectedToken] : std::views::zip(statement, ruleset)) {
        if (token != expectedToken) {
            return false;
        }
    }
    return true;
}
