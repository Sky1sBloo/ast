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
    std::string source = "a = 5;";
    int expectedValue = 5;

    variableHandler->allocate("a");

    Tokenizer tokens(source);
    ParseTreeBuilder treeBuilder(tokens.getTokens(), variableHandler);
    StatementContainer& tree = treeBuilder.getTree();
    tree.performAction();

    MemoryCell value = variableHandler->getValue("a");
    auto returnedValue = value.getAs<int>();
    if (returnedValue == std::nullopt) {
        std::string type;
        switch (value.getType()) {
        case DataType::INT:
            type = "int";
            break;
        case DataType::BOOL:
            type = "bool";
            break;
        case DataType::FLOAT:
            type = "float";
            break;
        case DataType::STRING:
            type = "string";
            break;
        case DataType::NULL_TYPE:
            type = "null";
            break;
        }
        FAIL() << "Returned variable value isn't at expected type. Type is: " << type;
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
    StatementContainer& tree = treeBuilder.getTree();
    tree.performAction();

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

TEST(PARSE_TREE_TESTS, VARIABLE_INITIALIZATION)
{
    std::shared_ptr<ProgramMemory> memory = std::make_shared<ProgramMemory>();
    std::shared_ptr<VariableHandler> variableHandler = std::make_shared<VariableHandler>(memory);
    std::string source = "var test;";

    Tokenizer tokens(source);
    ParseTreeBuilder treeBuilder(tokens.getTokens(), variableHandler);
    treeBuilder.getTree().performAction();

    MemoryCell valueA = variableHandler->getValue("test");
    if (valueA.getType() != DataType::NULL_TYPE) {
        FAIL() << "Returned variable isn't expected type NULL";
    }
} 

TEST(PARSE_TREE_TESTS, VARIABLE_INITIALIZATION_AND_ASSIGNMENT)
{
    /*
    std::shared_ptr<ProgramMemory> memory = std::make_shared<ProgramMemory>();
    std::shared_ptr<VariableHandler> variableHandler = std::make_shared<VariableHandler>(memory);
    std::string source = "var test = 5;";
    int expectedValue = 5;

    Tokenizer tokens(source);
    ParseTreeBuilder treeBuilder(tokens.getTokens(), variableHandler);
    auto tree = treeBuilder.getTree();
    tree->performAction();

    const MemoryCell& valueA = variableHandler->getValue("test");
    auto returnedValueA = valueA.getAs<int>();

    if (returnedValueA == std::nullopt) {
        FAIL() << "Returned variable isn't at expected type";
    }

    EXPECT_EQ(expectedValue, returnedValueA);  */
} 
