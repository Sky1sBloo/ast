#include "ParseNodes.hpp"
#include "ParserRulesets.hpp"

VariableInitializatonAndAssignmentRuleset::VariableInitializatonAndAssignmentRuleset(std::shared_ptr<VariableHandler> handler)
    : ParserRuleset(handler)
{
}

std::unique_ptr<Expr> VariableInitializatonAndAssignmentRuleset::createExpr(const std::vector<Token>& statement)
{
    if (!statementMatchesRuleset(statement, _ruleset)) {
        return nullptr;
    }

    const std::string& identifier = statement[1].getValue();
    const std::string& value = statement[3].getValue();

    auto initializationExpr = std::make_unique<InitializationExpr>(identifier, std::make_unique<LiteralExpr>(value), _handler);
    return std::make_unique<Expr>(std::move(initializationExpr));
}
