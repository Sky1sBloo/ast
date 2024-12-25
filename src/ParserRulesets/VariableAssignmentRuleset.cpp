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
    const std::string& value = statement[2].getValue();

    auto assignmentExpr = std::make_unique<AssignExpr>(identifier, std::make_unique<LiteralExpr>(value), _handler);
    return RulesetExpr{std::make_unique<Expr>(std::move(assignmentExpr))};
}
