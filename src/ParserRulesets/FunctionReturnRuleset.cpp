#include "ParseNodes.hpp"
#include "ParserRulesets.hpp"

FunctionReturnRuleset::FunctionReturnRuleset(std::shared_ptr<VariableHandler> handler)
    : ParserRuleset(handler)
{
}

RulesetExpr FunctionReturnRuleset::createExpr(const std::vector<Token>& statement) const
{
    if (!statementMatchesRuleset(statement, _ruleset)) {
        return RulesetExpr {};
    }

    const Token& value = statement[1];
    std::unique_ptr<ReturnableExpr> valueExpr;
    if (value.getSubType() == Token::SubTypes::IDENTIFIER) {
        valueExpr = std::make_unique<VariableIdentifier>(value.getValue(), _handler);
    } else if (value.getSubType() == Token::SubTypes::LITERAL) {
        valueExpr = std::make_unique<LiteralExpr>(value.getValue());
    }

    // Todo add support for identifier
    auto expr = std::make_unique<FunctionReturnExpr>(std::move(valueExpr));
    return RulesetExpr { std::make_unique<Expr>(std::move(expr)) };
}
