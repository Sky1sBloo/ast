#include "ParseTreeBuilder.hpp"
#include "ProgramMemory.hpp"
#include "Tokenizer.hpp"
#include "VariableHandler.hpp"

#include <gtest/gtest.h>
#include <optional>
#include <string>

TEST(PARSE_TREE_TESTS, VARIABLE_SAVING)
{
    std::shared_ptr<ProgramMemory> memory = std::make_shared<ProgramMemory>();
    std::shared_ptr<VariableHandler> variableHandler = std::make_shared<VariableHandler>(memory);
    std::string source = "a = 5";
    int expectedValue = 5;

    variableHandler->allocate("a");

    Tokenizer tokens(source);
    ParseTreeBuilder treeBuilder(tokens.getTokens(), variableHandler);
    auto tree = treeBuilder.getTree();
    tree->performAction();

    MemoryCell value = variableHandler->getValue("a");
    auto returnedValue = value.getAs<int>();
    if (returnedValue == std::nullopt) {
        FAIL() << "Returned variable value isn't at expected type";
    }

    EXPECT_EQ(expectedValue, returnedValue);
}

TEST(PARSE_TREE_TESTS, MULTIPLE_STATEMENTS)
{
    std::shared_ptr<ProgramMemory> memory = std::make_shared<ProgramMemory>();
    std::shared_ptr<VariableHandler> variableHandler = std::make_shared<VariableHandler>(memory);
    std::string source = "a = 5; b = 6; a = 3;";
    int expectedValueA = 3;
    int expectedValueB = 6;

    variableHandler->allocate("a");
    variableHandler->allocate("b");

    Tokenizer tokens(source);
    ParseTreeBuilder treeBuilder(tokens.getTokens(), variableHandler);
    auto tree = treeBuilder.getTree();
    tree->performAction();

    MemoryCell valueA = variableHandler->getValue("a");
    auto returnedValueA = valueA.getAs<int>();
    MemoryCell valueB = variableHandler->getValue("b");
    auto returnedValueB = valueB.getAs<int>();
    if (returnedValueA == std::nullopt || returnedValueB == std::nullopt) {
        FAIL() << "Returned variable value isn't at expected type";
    }

    EXPECT_EQ(expectedValueA, returnedValueA);
    EXPECT_EQ(expectedValueB, returnedValueB);
}
