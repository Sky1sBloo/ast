#include "ParseNodes.hpp"
#include "ParserRulesets.hpp"

VariableInitializationAndAssignmentRuleset::VariableInitializationAndAssignmentRuleset(std::shared_ptr<VariableHandler> handler)
    : ParserRuleset(handler)
{
}

RulesetExpr VariableInitializationAndAssignmentRuleset::createExpr(const std::vector<Token>& statement) const
{
    if (!statementMatchesRuleset(statement, _ruleset)) {
        return RulesetExpr{std::monostate{}};
    }

    const std::string& identifier = statement[1].getValue();
    const std::string& value = statement[3].getValue();

    auto initializationExpr = std::make_unique<InitializationExpr>(identifier, std::make_unique<LiteralExpr>(value), _handler);
    return RulesetExpr{std::make_unique<Expr>(std::move(initializationExpr))};
}
