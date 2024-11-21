#include "ParseNodes.hpp"
#include "ProgramMemory.hpp"
#include "VariableHandler.hpp"
#include "gtest/gtest.h"
#include <gtest/gtest.h>
#include <memory>
#include <string>

TEST(PARSE_NODES_TEST, INITIALIZATION_EXPR_TEST)
{
    std::shared_ptr<ProgramMemory> memory = std::make_shared<ProgramMemory>();
    std::shared_ptr<VariableHandler> varHandler = std::make_shared<VariableHandler>(memory);
    const std::string expectedValue = "5";
    int expectedVal = 5;
    const std::string testVar = "TestVar";

    InitializationExpr initExpr(testVar, std::make_unique<LiteralExpr>(expectedValue), varHandler);
    initExpr.performAction();
    EXPECT_NO_THROW({
        int retrievedValue = varHandler->getValue(testVar).getAs<int>().value();

        EXPECT_EQ(retrievedValue, expectedVal);
    });
}

TEST(PARSE_NODES_TEST, ASSIGNMENT_EXPR_TEST)
{
    std::shared_ptr<ProgramMemory> memory = std::make_shared<ProgramMemory>();
    std::shared_ptr<VariableHandler> varHandler = std::make_shared<VariableHandler>(memory);

    const std::string initialValue = "3";
    int expectInitValue = 3;
    const std::string expectedValue = "6";
    int expectFinalValue = 6;
    const std::string testVar = "TestVar";

    InitializationExpr initExpr(testVar, std::make_unique<LiteralExpr>(initialValue), varHandler);
    initExpr.performAction();
    int retrievedValue;
    EXPECT_NO_THROW({
        retrievedValue = varHandler->getValue(testVar).getAs<int>().value();
        EXPECT_EQ(retrievedValue, expectInitValue);
    });

    AssignExpr assignExpr(testVar, std::make_unique<LiteralExpr>(expectedValue), varHandler);
    assignExpr.performAction();
    retrievedValue = varHandler->getValue(testVar).getAs<int>().value();

    EXPECT_EQ(retrievedValue, expectFinalValue);
}

TEST(PARSE_NODES_TEST, STATEMENT_CONTAINER_TEST)
{
    std::shared_ptr<ProgramMemory> memory = std::make_shared<ProgramMemory>();
    std::shared_ptr<VariableHandler> varHandler = std::make_shared<VariableHandler>(memory);

    using InitAndAssign = std::pair<std::string, int>;
    InitAndAssign varA = { "varA", 5 };
    InitAndAssign varB = { "varB", 6 };
    InitAndAssign assignA = { "varA", 10 };

    StatementContainer statementContainer;
    auto varAExpr = std::make_unique<InitializationExpr>(varA.first, std::make_unique<LiteralExpr>(std::to_string(varA.second)), varHandler);
    auto varBExpr = std::make_unique<InitializationExpr>(varB.first, std::make_unique<LiteralExpr>(std::to_string(varB.second)), varHandler);
    auto assignAExpr = std::make_unique<AssignExpr>(varA.first, std::make_unique<LiteralExpr>(std::to_string(assignA.second)), varHandler);
    statementContainer.insertExpr(std::make_unique<Expr>(std::move(varAExpr)));
    statementContainer.insertExpr(std::make_unique<Expr>(std::move(varBExpr)));
    statementContainer.insertExpr(std::make_unique<Expr>(std::move(assignAExpr)));

    statementContainer.performAction();

    EXPECT_NO_THROW({
        int retrievedValue = varHandler->getValue(varA.first).getAs<int>().value();
        EXPECT_EQ(retrievedValue, assignA.second);
        retrievedValue = varHandler->getValue(varB.first).getAs<int>().value();
        EXPECT_EQ(retrievedValue, varB.second);
    });
}

TEST(PARSE_NODES_TEST, FUNCTION_EXPR_TEST)
{
    std::shared_ptr<ProgramMemory> memory = std::make_shared<ProgramMemory>();
    std::shared_ptr<VariableHandler> varHandler = std::make_shared<VariableHandler>(memory);
    const std::string identifier = "testVar";
    int value = 5;
    int secondValue = 10;
    int returnValue = 7;

    FunctionExpr functionExpr("testFunc");
    auto varExpr = std::make_unique<InitializationExpr>(identifier, std::make_unique<LiteralExpr>(std::to_string(value)), varHandler);
    auto assignExpr = std::make_unique<AssignExpr>(identifier, std::make_unique<LiteralExpr>(std::to_string(secondValue)), varHandler);
    auto returnLiteral = std::make_unique<LiteralExpr>(std::to_string(returnValue));

    functionExpr.insertExpr(std::make_unique<Expr>(std::move(varExpr)));
    functionExpr.insertExpr(std::make_unique<Expr>(std::move(assignExpr)));
    functionExpr.insertExpr(std::make_unique<Expr>(std::move(returnLiteral)));

    EXPECT_NO_THROW({ 
        int retrievedValue = functionExpr.getValue().getAs<int>().value();
        EXPECT_EQ(retrievedValue, returnValue);
        int retrievedVariableValue = varHandler->getValue(identifier).getAs<int>().value();
        EXPECT_EQ(retrievedVariableValue, secondValue);
    });
}
