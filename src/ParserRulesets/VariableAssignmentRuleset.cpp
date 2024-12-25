#include "ParseNodes.hpp"
#include "ParserRulesets.hpp"
#include <memory>

VariableAssignmentRuleset::VariableAssignmentRuleset(std::shared_ptr<VariableHandler> handler)
    : ParserRuleset(handler)
{
}

std::unique_ptr<Expr> VariableAssignmentRuleset::createExpr(const std::vector<Token>& statement) 
{
    if (!statementMatchesRuleset(statement, _ruleset)) {
        return nullptr;
    }

    const std::string& identifier = statement[0].getValue();
    const std::string& value = statement[2].getValue();

    auto assignmentExpr = std::make_unique<AssignExpr>(identifier, std::make_unique<LiteralExpr>(value), _handler);
    return std::make_unique<Expr>(std::move(assignmentExpr));
}
