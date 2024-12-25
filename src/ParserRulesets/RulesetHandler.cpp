#include "RulesetHandler.hpp"
#include <stdexcept>

RulesetHandler::RulesetHandler(std::shared_ptr<VariableHandler> handler)
{
    _rulesets.push_back(std::make_unique<VariableInitializationRuleset>(handler));
    _rulesets.push_back(std::make_unique<VariableAssignmentRuleset>(handler));
    _rulesets.push_back(std::make_unique<VariableInitializationAndAssignmentRuleset>(handler));
}

std::unique_ptr<Expr> RulesetHandler::getExpression(const std::vector<Token>& statement)
{
    for (const auto& ruleset : _rulesets) {
        std::unique_ptr<Expr> expr = ruleset->createExpr(statement);
        if (expr != nullptr) {
            return std::move(expr);
        }
    }

    throw std::invalid_argument("Statement ruleset is unkown");
}
