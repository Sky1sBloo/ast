#include <gtest/gtest.h>
#include <memory>

#include "ProgramMemory.hpp"
#include "VariableHandler.hpp"

TEST(VARIABLE_HANDLER_TESTS, ASSIGNMENT)
{
    std::shared_ptr<ProgramMemory> memory = std::make_shared<ProgramMemory>();
    VariableHandler variableHandler(memory);

    const std::string variableName = "TestVar";
    const std::string variableValue = "5.f";

    EXPECT_NO_THROW({ variableHandler.allocate(variableName, variableValue); });

    EXPECT_NO_THROW({ EXPECT_EQ(variableValue, variableHandler.getValue(variableName)); });
}
