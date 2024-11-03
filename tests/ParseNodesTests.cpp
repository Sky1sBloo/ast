#include "ParseNodes.hpp"
#include "ProgramMemory.hpp"
#include "VariableHandler.hpp"
#include <gtest/gtest.h>
#include <memory>

TEST(PARSE_NOTES_TEST, INITIALIZATION_EXPR_TEST)
{
    std::shared_ptr<ProgramMemory> memory = std::make_shared<ProgramMemory>();
    std::shared_ptr<VariableHandler> varHandler = std::make_shared<VariableHandler>(memory);
    const std::string expectedValue = "5";
    int expectedVal = 5;
    const std::string testVar = "TestVar";

    InitializationExpr initExpr(testVar, std::make_unique<LiteralExpr>(DataType::INT, expectedValue), varHandler);
    initExpr.performAction();
    EXPECT_NO_THROW({
        int retrievedValue = varHandler->getValue(testVar).getAs<int>().value();

        EXPECT_EQ(retrievedValue, expectedVal);
    });
}

TEST(PARSE_NOTES_TEST, ASSIGNMENT_EXPR_TEST)
{
    std::shared_ptr<ProgramMemory> memory = std::make_shared<ProgramMemory>();
    std::shared_ptr<VariableHandler> varHandler = std::make_shared<VariableHandler>(memory);

    const std::string initialValue = "3";
    int expectInitValue = 3;
    const std::string expectedValue = "6";
    int expectFinalValue = 6;
    const std::string testVar = "TestVar";

    InitializationExpr initExpr(testVar, std::make_unique<LiteralExpr>(DataType::INT, initialValue), varHandler);
    initExpr.performAction();
    int retrievedValue;
    EXPECT_NO_THROW({
        retrievedValue = varHandler->getValue(testVar).getAs<int>().value();
        EXPECT_EQ(retrievedValue, expectInitValue);
    });

    AssignExpr assignExpr(testVar, std::make_unique<LiteralExpr>(DataType::INT, expectedValue), varHandler);
    assignExpr.performAction();
    retrievedValue = varHandler->getValue(testVar).getAs<int>().value();

    EXPECT_EQ(retrievedValue, expectFinalValue);
}
