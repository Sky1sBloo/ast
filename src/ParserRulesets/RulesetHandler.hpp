#pragma once

#include "BaseParseNodes.hpp"
#include "ParserRulesets.hpp"
#include "Token.hpp"
#include "VariableHandler.hpp"
#include <memory>

/**
 * Class for handling rulesets
 */
class RulesetHandler {
public:
    RulesetHandler(std::shared_ptr<VariableHandler> handler);

    /**
     * Checks all rulesets and returns an expression
     *
     * @throws invalid_argument if it doesnt match any ruleset
    */
    std::unique_ptr<Expr> getExpression(const std::vector<Token>& statement);

private:
    std::vector<std::unique_ptr<ParserRuleset>> _rulesets;
};
