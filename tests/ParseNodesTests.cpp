#include <gtest/gtest.h>
#include <memory>
#include "ParseNodes.hpp"
#include "ProgramMemory.hpp"

TEST(PARSE_NOTES_TEST, INITIALIZATION_EXPR_TEST)
{
    std::shared_ptr<ProgramMemory> memory = std::make_shared<ProgramMemory>();
    const std::string expectedValue = "5";

    InitializationExpr initExpr(std::make_unique<LiteralExpr>(DataType::INT, expectedValue), memory);
    initExpr.performAction();
    std::string retrievedValue = memory->retrieve(0);

    EXPECT_EQ(retrievedValue, expectedValue);
}

TEST(PARSE_NOTES_TEST, ASSIGNMENT_EXPR_TEST)
{
    std::shared_ptr<ProgramMemory> memory = std::make_shared<ProgramMemory>();

    const std::string initialValue = "3";
    const std::string expectedValue = "6";
    const int addr = 0;

    InitializationExpr initExpr(std::make_unique<LiteralExpr>(DataType::INT, initialValue), memory);
    initExpr.performAction();
    std::string retrievedValue = memory->retrieve(addr);

    EXPECT_EQ(retrievedValue, initialValue);

    AssignExpr assignExpr(addr, std::make_unique<LiteralExpr>(DataType::INT, expectedValue), memory);
    assignExpr.performAction();
    retrievedValue = memory->retrieve(addr);

    EXPECT_EQ(retrievedValue, expectedValue);
}
