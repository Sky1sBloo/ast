#include "ParserRulesets.hpp"

FunctionTerminationRuleset::FunctionTerminationRuleset(std::shared_ptr<VariableHandler> handler)
    : ParserRuleset(handler)
{
}

RulesetExpr FunctionTerminationRuleset::createExpr(const std::vector<Token>& statement) const
{
    if (statement.size() != 1) {
        return RulesetExpr {};
    }
    if (statement[0] != _ruleset) {
        return RulesetExpr {};
    }
    return RulesetExpr { RulesetExpr::Types::FUNCTION_TERMINATION };
}
