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

    EXPECT_EQ(RulesetExpr::Types::FUNCTION_DEFINITION, rulesetExpr.getTypes());
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

    EXPECT_EQ(RulesetExpr::Types::FUNCTION_DEFINITION, singleRulesetExpr.getTypes());
    EXPECT_EQ(RulesetExpr::Types::FUNCTION_DEFINITION, multiRulesetExpr.getTypes());
    singleRulesetExpr.visit([](std::unique_ptr<Expr>&) {}, [](std::unique_ptr<FunctionDefinition>& func) {
        std::vector<std::string> singleParamExpected = { "param1" };
        EXPECT_EQ(singleParamExpected.size(), func->getParams().size());
        EXPECT_TRUE(std::ranges::equal(singleParamExpected, func->getParams())); }, []() {}, []() {});
    multiRulesetExpr.visit([](std::unique_ptr<Expr>&) {}, [](std::unique_ptr<FunctionDefinition>& func) {
        std::vector<std::string> multiParamExpected = { "param1", "param2", "param3" };
        EXPECT_EQ(multiParamExpected.size(), func->getParams().size());
        EXPECT_TRUE(std::ranges::equal(multiParamExpected, func->getParams())); }, []() {}, []() {});
}
