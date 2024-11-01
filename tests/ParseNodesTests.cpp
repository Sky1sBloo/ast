#include <gtest/gtest.h>
#include <memory>
#include "ParseNodes.hpp"
#include "ProgramMemory.hpp"

TEST(PARSE_NOTES_TEST, INITIALIZATION_EXPR_TEST)
{
    std::shared_ptr<ProgramMemory> memory;
    const std::string expectedValue = "5";

    InitializationExpr initExpr(std::make_unique<LiteralExpr>(DataType::INT, expectedValue), memory);
    initExpr.performAction();
    std::string retrievedValue = memory->retrieve(1);

    EXPECT_EQ(retrievedValue, expectedValue);
}

TEST(PARSE_NOTES_TEST, ASSIGNMENT_EXPR_TEST)
{
    std::shared_ptr<ProgramMemory> memory;

    const std::string initialValue = "3";
    const std::string expectedValue = "6";

    InitializationExpr initExpr(std::make_unique<LiteralExpr>(DataType::INT, initialValue), memory);
    initExpr.performAction();
    std::string retrievedValue = memory->retrieve(1);

    EXPECT_EQ(retrievedValue, initialValue);

    AssignExpr assignExpr(1, std::make_unique<LiteralExpr>(DataType::INT, expectedValue), memory);
    assignExpr.performAction();
    retrievedValue = memory->retrieve(1);

    EXPECT_EQ(retrievedValue, expectedValue);
}
