#include "BaseParseNodes.hpp"
#include "ParseNodes.hpp"
#include "ParserRulesets.hpp"
#include <memory>

VariableAssignmentRuleset::VariableAssignmentRuleset(std::shared_ptr<VariableHandler> handler)
    : ParserRuleset(handler)
{
}

RulesetExpr VariableAssignmentRuleset::createExpr(const std::vector<Token>& statement) const
{
    if (!statementMatchesRuleset(statement, _ruleset)) {
        return RulesetExpr{std::monostate()};
    }

    const std::string& identifier = statement[0].getValue();
    const Token& value = statement[2];
    std::unique_ptr<ReturnableExpr> valueExpr;
    if (value.getSubType() == Token::SubTypes::IDENTIFIER) {
        valueExpr = std::make_unique<VariableIdentifier>(value.getValue(), _handler);
    } else if (value.getSubType() == Token::SubTypes::LITERAL){
        valueExpr = std::make_unique<LiteralExpr>(value.getValue());
    }

    auto assignmentExpr = std::make_unique<AssignExpr>(identifier, std::move(valueExpr), _handler);
    return RulesetExpr{std::make_unique<Expr>(std::move(assignmentExpr))};
}
