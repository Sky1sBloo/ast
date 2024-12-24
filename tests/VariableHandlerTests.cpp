#include <gtest/gtest.h>
#include <memory>
#include <stdexcept>

#include "ProgramMemory.hpp"
#include "VariableHandler.hpp"

TEST(VARIABLE_HANDLER_TESTS, INITIALIAZATION)
{
    std::shared_ptr<ProgramMemory> memory = std::make_shared<ProgramMemory>();
    VariableHandler variableHandler(memory);

    const std::string variableName = "TestVar";
    const std::string variableValue = "5.0";
    float expectedValue = 5.f;

    EXPECT_NO_THROW({ variableHandler.allocate(variableName, variableValue); });

    EXPECT_NO_THROW({
        float value = variableHandler.getValue(variableName).getAs<float>().value();
        EXPECT_FLOAT_EQ(expectedValue, value);
    });
}

TEST(VARIABLE_HANDLER_TESTS, ASSIGNMENT)
{
    std::shared_ptr<ProgramMemory> memory = std::make_shared<ProgramMemory>();
    VariableHandler variableHandler(memory);

    const std::string variableName = "TestVar";
    const std::string variableValue = "5.0";
    const std::string newValue = "10.0";
    float expectedValue = 10.f;
    variableHandler.allocate(variableName, variableValue);

    variableHandler.setValue(variableName, newValue);

    EXPECT_NO_THROW({
        float value = variableHandler.getValue(variableName).getAs<float>().value();
        EXPECT_FLOAT_EQ(expectedValue, value);
    });
}

TEST(VARIABLE_HANDLER_TESTS, SCOPE_HANDLING)
{
    std::shared_ptr<ProgramMemory> memory = std::make_shared<ProgramMemory>();
    VariableHandler variableHandler(memory);

    const std::string outerVarName = "OuterScope";
    const std::string outerVarValue = "\"Cabloosh\"";
    const std::string innerVarName = "InnerScope";
    const std::string innerVarValue = "\"Bingo\"";

    variableHandler.allocate(outerVarName, outerVarValue);
    variableHandler.allocateStackFrame();
    variableHandler.allocate(innerVarName, innerVarValue);

    EXPECT_NO_THROW({
        const std::string retrievedOuter = variableHandler.getValue(outerVarName).getAs<std::string>().value();
        EXPECT_EQ(retrievedOuter, outerVarValue);
        const std::string retrievedInner = variableHandler.getValue(innerVarName).getAs<std::string>().value();
        EXPECT_EQ(retrievedInner, innerVarValue);
    });
    variableHandler.deallocateStackFrame();

    EXPECT_NO_THROW({
        const std::string retrievedOuter = variableHandler.getValue(outerVarName).getAs<std::string>().value();
        EXPECT_EQ(retrievedOuter, outerVarValue);
    });

    EXPECT_THROW({ const std::string retrievedInner = variableHandler.getValue(innerVarName).getAs<std::string>().value(); }, BadVariableHandling);
}

TEST(VARIABLE_HANDLER_TESTS, SCOPE_SAME_NAME)
{
    std::shared_ptr<ProgramMemory> memory = std::make_shared<ProgramMemory>();
    VariableHandler variableHandler(memory);

    const std::string outerVarName = "SameName";
    const std::string outerVarValue = "\"Cabloosh\"";
    const std::string innerVarValue = "\"Bingo\"";

    variableHandler.allocate(outerVarName, outerVarValue);
    variableHandler.allocateStackFrame();
    variableHandler.allocate(outerVarName, innerVarValue);
    EXPECT_NO_THROW({
        const std::string retrievedInner = variableHandler.getValue(outerVarName).getAs<std::string>().value();
        EXPECT_EQ(retrievedInner, innerVarValue);
    });

    variableHandler.deallocateStackFrame();

    EXPECT_NO_THROW({
        const std::string retrievedOuter = variableHandler.getValue(outerVarName).getAs<std::string>().value();
        EXPECT_EQ(retrievedOuter, outerVarValue);
    });
}
