#include "ParserRulesets.hpp"

FunctionTerminationRuleset::FunctionTerminationRuleset(std::shared_ptr<VariableHandler> handler)
    : ParserRuleset(handler)
{
}

RulesetExpr FunctionTerminationRuleset::createExpr(const std::vector<Token>& statement) const
{
    if (statement.size() != 1) {
        return std::monostate();
    }
    if (statement[0] != _ruleset) {
        return std::monostate();
    }
    return RulesetExpr{ FunctionTermination {}};
}
