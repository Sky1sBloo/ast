#include <gtest/gtest.h>
#include <memory>
#include "ParseNodes.hpp"
#include "ProgramMemory.hpp"
#include "VariableHandler.hpp"

TEST(PARSE_NOTES_TEST, INITIALIZATION_EXPR_TEST)
{
    std::shared_ptr<ProgramMemory> memory = std::make_shared<ProgramMemory>();
    std::shared_ptr<VariableHandler> varHandler = std::make_shared<VariableHandler>(memory);
    const std::string expectedValue = "5";
    const std::string testVar = "TestVar";

    InitializationExpr initExpr(testVar, std::make_unique<LiteralExpr>(DataType::INT, expectedValue), varHandler);
    initExpr.performAction();
    std::string retrievedValue = varHandler->getValue(testVar);

    EXPECT_EQ(retrievedValue, expectedValue);
}

TEST(PARSE_NOTES_TEST, ASSIGNMENT_EXPR_TEST)
{
    std::shared_ptr<ProgramMemory> memory = std::make_shared<ProgramMemory>();
    std::shared_ptr<VariableHandler> varHandler = std::make_shared<VariableHandler>(memory);

    const std::string initialValue = "3";
    const std::string expectedValue = "6";
    const std::string testVar = "TestVar";

    InitializationExpr initExpr(testVar, std::make_unique<LiteralExpr>(DataType::INT, initialValue), varHandler);
    initExpr.performAction();
    std::string retrievedValue = varHandler->getValue(testVar);

    EXPECT_EQ(retrievedValue, initialValue);

    AssignExpr assignExpr(testVar, std::make_unique<LiteralExpr>(DataType::INT, expectedValue), varHandler);
    assignExpr.performAction();
    retrievedValue = varHandler->getValue(testVar);

    EXPECT_EQ(retrievedValue, expectedValue);
}
