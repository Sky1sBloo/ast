#include <gtest/gtest.h>
#include <memory>
#include "ParseNodes.hpp"
#include "ProgramMemory.hpp"

TEST(PARSE_NOTES_TEST, INITIALIZATION_EXPR_TEST)
{
    std::shared_ptr<ProgramMemory> memory;
    const std::string expectedValue = "5";

    InitializationExpr initExpr(std::make_unique<LiteralExpr>(DataType::INT, expectedValue), memory);
    std::string retrievedValue = memory->retrieve(1);

    EXPECT_EQ(expectedValue, retrievedValue);
}
