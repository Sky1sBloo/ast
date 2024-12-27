#include "ParserRulesets/ParserRulesets.hpp"
#include <ranges>

bool ParserRuleset::statementMatchesRuleset(const std::vector<Token>& statement, const std::vector<Token>& ruleset)
{
    if (statement.size() != ruleset.size()) {
        return false;
    }

    for (const auto& [token, expectedToken] : std::views::zip(statement, ruleset)) {
        if (token != expectedToken) {
            return false;
        }
    }
    return true;
}
