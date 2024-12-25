#include "ParseNodes.hpp"
#include "ParserRulesets.hpp"
#include <memory>

VariableInitializationRuleset::VariableInitializationRuleset(std::shared_ptr<VariableHandler> handler)
    : ParserRuleset(handler)
{
}

std::unique_ptr<Expr> VariableInitializationRuleset::createExpr(const std::vector<Token>& statement) const
{
    if (!statementMatchesRuleset(statement, _ruleset)) {
        return nullptr;
    }

    const std::string& identifier = statement[1].getValue();
    auto identifierExpr = std::make_unique<InitializationExpr>(identifier, _handler);
    return std::make_unique<Expr>(std::move(identifierExpr));
}
