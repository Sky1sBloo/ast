#include "FunctionDefinition.hpp"
#include "ParserRulesets/RulesetHandler.hpp"
#include "Token.hpp"
#include <gtest/gtest.h>
#include <variant>

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
    std::vector<Token> singleParamStatement = { { { Token::SubTypes::KEYWORD, "func" },
        { Token::SubTypes::IDENTIFIER, "test" },
        { Token::SubTypes::BRACE, "(" },
        { Token::SubTypes::IDENTIFIER, "param1" },
        { Token::SubTypes::BRACE, ")" },
        { Token::SubTypes::BRACE, "{" } } };
    std::vector<Token> multiParamStatement = { { { Token::SubTypes::KEYWORD, "func" },
        { Token::SubTypes::IDENTIFIER, "test" },
        { Token::SubTypes::BRACE, "(" },
        { Token::SubTypes::IDENTIFIER, "param1" },
        { Token::SubTypes::OPERATOR, "," },
        { Token::SubTypes::IDENTIFIER, "param2" },
        { Token::SubTypes::OPERATOR, "," },
        { Token::SubTypes::IDENTIFIER, "param3" },
        { Token::SubTypes::BRACE, ")" },
        { Token::SubTypes::BRACE, "{" } } };

    std::shared_ptr<ProgramMemory> memory = std::make_shared<ProgramMemory>();
    std::shared_ptr<VariableHandler> varHandler = std::make_shared<VariableHandler>(memory);

    RulesetHandler handler(varHandler);

    RulesetExpr singleRulesetExpr = handler.getExpression(singleParamStatement);
    RulesetExpr multiRulesetExpr = handler.getExpression(multiParamStatement);

    EXPECT_TRUE(std::holds_alternative<std::unique_ptr<FunctionDefinition>>(singleRulesetExpr));
    EXPECT_TRUE(std::holds_alternative<std::unique_ptr<FunctionDefinition>>(multiRulesetExpr));
    auto singleFuncExpr = std::move(std::get<std::unique_ptr<FunctionDefinition>>(singleRulesetExpr));
    auto multiFuncExpr = std::move(std::get<std::unique_ptr<FunctionDefinition>>(multiRulesetExpr));

    std::vector<std::string> singleParamExpected = { "param1" };
    std::vector<std::string> multiParamExpected = { "param1", "param2", "param3" };

    EXPECT_EQ(singleParamExpected.size(), singleFuncExpr->getParams().size());
    EXPECT_TRUE(std::ranges::equal(singleParamExpected, singleFuncExpr->getParams()));
    EXPECT_EQ(multiParamExpected.size(), multiFuncExpr->getParams().size());
    EXPECT_TRUE(std::ranges::equal(multiParamExpected, multiFuncExpr->getParams()));
}
