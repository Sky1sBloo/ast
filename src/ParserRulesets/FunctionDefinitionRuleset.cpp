#include "FunctionDefinition.hpp"
#include "ParserRulesets.hpp"
#include "Token.hpp"
#include <algorithm>
#include <iostream>
#include <stdexcept>

FunctionDefinitionRuleset::FunctionDefinitionRuleset(std::shared_ptr<VariableHandler> handler)
    : ParserRuleset(handler)
{
}

RulesetExpr FunctionDefinitionRuleset::createExpr(const std::vector<Token>& statement) const
{
    if (statement.size() < _openingRuleset.size() + _closingRuleset.size()) {
        return RulesetExpr { std::monostate() };
    }

    // To check for constant ruleset ends doesnt match
    if (!std::equal(_openingRuleset.begin(), _openingRuleset.end(), statement.begin())
        || !std::equal(_closingRuleset.rbegin(), _closingRuleset.rend(), statement.rbegin())) {
        return RulesetExpr { std::monostate() };
    }

    std::vector<std::string> params;
    try {
        params = getFunctionParams(statement);
    } catch (const std::invalid_argument& ev) {
        return RulesetExpr { std::monostate() };
    }

    const std::string& identifier = statement[1].getValue();
    std::unique_ptr<FunctionDefinition> functionExpr;

    functionExpr = std::make_unique<FunctionDefinition>(identifier, params);
    return RulesetExpr { std::move(functionExpr) };
}

std::vector<std::string> FunctionDefinitionRuleset::getFunctionParams(const std::vector<Token>& statement) const
{
    std::vector<std::string> params;

    int paramStartIdx = _openingRuleset.size();
    int paramEndIdx = statement.size() - paramStartIdx;

    for (int i = paramStartIdx; i <= paramEndIdx; i += 2) {
        if (statement[i] != _parameterRuleset[0]) {
            throw std::invalid_argument("First param does not match ruleset");
            // Throw error
        }
        if (i != paramStartIdx && statement[i + 1] != _parameterRuleset[1]) {
            throw std::invalid_argument("No commas between params");
        }
        params.push_back(statement[i].getValue());
    }

    return params;
}
