#include "ParseNodes.hpp"
#include "ParserRulesets.hpp"
#include <memory>

VariableInitializationRuleset::VariableInitializationRuleset(std::shared_ptr<VariableHandler> handler)
    : ParserRuleset(handler)
{
}

RulesetExpr VariableInitializationRuleset::createExpr(const std::vector<Token>& statement) const
{
    if (!statementMatchesRuleset(statement, _ruleset)) {
        return RulesetExpr {};
    }

    const std::string& identifier = statement[1].getValue();
    auto identifierExpr = std::make_unique<InitializationExpr>(identifier, _handler);
    return RulesetExpr { std::make_unique<Expr>(std::move(identifierExpr)) };
}
