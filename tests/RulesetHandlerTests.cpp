#include "FunctionDefinition.hpp"
#include "ParserRulesets/RulesetHandler.hpp"
#include "Token.hpp"
#include <gtest/gtest.h>
#include <variant>
#include <ranges>

TEST(RULESET_HANDLER, FUNCTION_DEFINITION)
{
    std::vector<Token> statement = { { { Token::SubTypes::KEYWORD, "func" },
        { Token::SubTypes::IDENTIFIER, "test" },
        { Token::SubTypes::BRACE, "(" },
        { Token::SubTypes::BRACE, ")" },
        { Token::SubTypes::BRACE, "{" } } };

    std::shared_ptr<ProgramMemory> memory = std::make_shared<ProgramMemory>();
    std::shared_ptr<VariableHandler> varHandler = std::make_shared<VariableHandler>(memory);

    RulesetHandler handler(varHandler);
    RulesetExpr rulesetExpr = handler.getExpression(statement);

    EXPECT_TRUE(std::holds_alternative<std::unique_ptr<FunctionDefinition>>(rulesetExpr));
}

TEST(RULESET_HANDLER, FUNCTION_DEFINITION_PARAM)
{
    std::vector<Token> statement = { { { Token::SubTypes::KEYWORD, "func" },
        { Token::SubTypes::IDENTIFIER, "test" },
        { Token::SubTypes::BRACE, "(" },
        { Token::SubTypes::IDENTIFIER, "param1" },
        { Token::SubTypes::BRACE, ")" },
        { Token::SubTypes::BRACE, "{" } } };

    std::shared_ptr<ProgramMemory> memory = std::make_shared<ProgramMemory>();
    std::shared_ptr<VariableHandler> varHandler = std::make_shared<VariableHandler>(memory);

    RulesetHandler handler(varHandler);
    RulesetExpr rulesetExpr = handler.getExpression(statement);

    EXPECT_TRUE(std::holds_alternative<std::unique_ptr<FunctionDefinition>>(rulesetExpr));
    auto functionExpr = std::move(std::get<std::unique_ptr<FunctionDefinition>>(rulesetExpr));

    std::vector<std::string> expectedParams = { "param1" };

    EXPECT_TRUE(std::ranges::equal(expectedParams, functionExpr->getParams()));
}
