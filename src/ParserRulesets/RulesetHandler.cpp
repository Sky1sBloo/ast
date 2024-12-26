#include "RulesetHandler.hpp"
#include "ParserRulesets/ParserRulesets.hpp"
#include <stdexcept>
#include <variant>

RulesetHandler::RulesetHandler(std::shared_ptr<VariableHandler> handler)
{
    _rulesets.push_back(std::make_unique<VariableInitializationRuleset>(handler));
    _rulesets.push_back(std::make_unique<VariableAssignmentRuleset>(handler));
    _rulesets.push_back(std::make_unique<VariableInitializationAndAssignmentRuleset>(handler));
    _rulesets.push_back(std::make_unique<FunctionDefinitionRuleset>(handler));
}

RulesetExpr RulesetHandler::getExpression(const std::vector<Token>& statement)
{
    for (const auto& ruleset : _rulesets) {
        RulesetExpr rulesetExpr = ruleset->createExpr(statement);
        if (!std::holds_alternative<std::monostate>(rulesetExpr)) {
            return rulesetExpr;
        }
    }

    throw std::invalid_argument("Statement ruleset is unkown");
}
