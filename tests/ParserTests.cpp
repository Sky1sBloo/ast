#include "FunctionContainer.hpp"
#include "MemoryCell.hpp"
#include "ParseNodes.hpp"
#include "Parser.hpp"
#include "ProgramMemory.hpp"
#include "Tokenizer.hpp"
#include "VariableHandler.hpp"
#include <gtest/gtest.h>
#include <optional>

TEST(PARSE_TESTS, VARIABLE_SAVING)
{
    std::shared_ptr<ProgramMemory> memory = std::make_shared<ProgramMemory>();
    std::shared_ptr<VariableHandler> variableHandler = std::make_shared<VariableHandler>(memory);
    std::shared_ptr<FunctionContainer> functionContainer = std::make_shared<FunctionContainer>(variableHandler);
    std::string source = "a=5;";
    int expectedValue = 5;

    variableHandler->allocate("a");

    Tokenizer tokens(source);

    Parser treeBuilder(tokens.getTokens(), variableHandler, functionContainer);
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

TEST(PARSE_TESTS, MULTIPLE_STATEMENTS)
{
    std::shared_ptr<ProgramMemory> memory = std::make_shared<ProgramMemory>();
    std::shared_ptr<VariableHandler> variableHandler = std::make_shared<VariableHandler>(memory);
    std::shared_ptr<FunctionContainer> functionContainer = std::make_shared<FunctionContainer>(variableHandler);
    std::string source = "a = 5; b = 6; a = 3;";
    int expectedValueA = 3;
    int expectedValueB = 6;

    variableHandler->allocate("a");
    variableHandler->allocate("b");

    Tokenizer tokens(source);
    Parser treeBuilder(tokens.getTokens(), variableHandler, functionContainer);
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

TEST(PARSE_TESTS, VARIABLE_ASSIGN_TO_VARIABLE)
{
    std::shared_ptr<ProgramMemory> memory = std::make_shared<ProgramMemory>();
    std::shared_ptr<VariableHandler> variableHandler = std::make_shared<VariableHandler>(memory);
    std::shared_ptr<FunctionContainer> functionContainer = std::make_shared<FunctionContainer>(variableHandler);
    std::string source = "a = 5; b = a; a = 3;";
    int expectedValueA = 3;
    int expectedValueB = 5;

    variableHandler->allocate("a");
    variableHandler->allocate("b");

    Tokenizer tokens(source);
    Parser treeBuilder(tokens.getTokens(), variableHandler, functionContainer);
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

TEST(PARSE_TESTS, VARIABLE_INITIALIZATION)
{
    std::shared_ptr<ProgramMemory> memory = std::make_shared<ProgramMemory>();
    std::shared_ptr<VariableHandler> variableHandler = std::make_shared<VariableHandler>(memory);
    std::shared_ptr<FunctionContainer> functionContainer = std::make_shared<FunctionContainer>(variableHandler);
    std::string source = "var test;";

    Tokenizer tokens(source);
    Parser treeBuilder(tokens.getTokens(), variableHandler, functionContainer);
    treeBuilder.getTree().performAction();

    MemoryCell valueA = variableHandler->getValue("test");
    if (valueA.getType() != DataType::NULL_TYPE) {
        FAIL() << "Returned variable isn't expected type NULL";
    }
}

TEST(PARSE_TESTS, VARIABLE_INITIALIZATION_AND_ASSIGNMENT)
{
    std::shared_ptr<ProgramMemory> memory = std::make_shared<ProgramMemory>();
    std::shared_ptr<VariableHandler> variableHandler = std::make_shared<VariableHandler>(memory);
    std::shared_ptr<FunctionContainer> functionContainer = std::make_shared<FunctionContainer>(variableHandler);
    std::string source = "var test = 5;";
    int expectedValue = 5;

    Tokenizer tokens(source);
    Parser treeBuilder(tokens.getTokens(), variableHandler, functionContainer);
    treeBuilder.getTree().performAction();

    const MemoryCell& valueA = variableHandler->getValue("test");
    auto returnedValueA = valueA.getAs<int>();

    if (returnedValueA == std::nullopt) {
        FAIL() << "Returned variable isn't at expected type";
    }

    EXPECT_EQ(expectedValue, returnedValueA);
}

TEST(PARSE_TESTS, INVALID_KEYWORD)
{
    std::shared_ptr<ProgramMemory> memory = std::make_shared<ProgramMemory>();
    std::shared_ptr<VariableHandler> variableHandler = std::make_shared<VariableHandler>(memory);
    std::shared_ptr<FunctionContainer> functionContainer = std::make_shared<FunctionContainer>(variableHandler);
    std::string source = "shit test = 5;";
    int expectedValue = 5;

    Tokenizer tokens(source);
    EXPECT_THROW(Parser treeBuilder(tokens.getTokens(), variableHandler, functionContainer), std::invalid_argument);
}

TEST(PARSE_TESTS, FUNCTION_DEFINITION)
{
    std::shared_ptr<ProgramMemory> memory = std::make_shared<ProgramMemory>();
    std::shared_ptr<VariableHandler> variableHandler = std::make_shared<VariableHandler>(memory);
    std::shared_ptr<FunctionContainer> functionContainer = std::make_shared<FunctionContainer>(variableHandler);
    std::string source = "var a = \"str\"; func testFunc() { a = 5; }";
    int expectedValue = 5;

    Tokenizer tokens(source);
    Parser treeBuilder(tokens.getTokens(), variableHandler, functionContainer);
    treeBuilder.getTree().performAction();

    FunctionCallExpr expr { "testFunc", functionContainer, variableHandler };
    const MemoryCell& cell = expr.getValue();
    EXPECT_EQ(cell.getType(), DataType::NULL_TYPE);

    const MemoryCell& varA = variableHandler->getValue("a");
    auto retrievedVarA = varA.getAs<int>();

    if (retrievedVarA == std::nullopt) {
        FAIL() << "Returned variable isn't at expected type. Current Type: " << static_cast<int>(varA.getType()) << std::endl;
    }
    EXPECT_EQ(expectedValue, retrievedVarA);
}

TEST(PARSE_TESTS, FUNCTION_PARAM_TEST)
{
    std::shared_ptr<ProgramMemory> memory = std::make_shared<ProgramMemory>();
    std::shared_ptr<VariableHandler> variableHandler = std::make_shared<VariableHandler>(memory);
    std::shared_ptr<FunctionContainer> functionContainer = std::make_shared<FunctionContainer>(variableHandler);
    std::string source = "var a = \"str\"; func testFunc(param) { a = param; param = 2; return param; }";
    int expectedValue = 5;

    Tokenizer tokens(source);
    Parser treeBuilder(tokens.getTokens(), variableHandler, functionContainer);
    treeBuilder.getTree().performAction();

    FunctionCallExpr expr { "testFunc", functionContainer, variableHandler };
    expr.insertParam(std::make_unique<LiteralExpr>(std::to_string(expectedValue)));

    const MemoryCell& cell = expr.getValue();
    EXPECT_EQ(cell.getType(), DataType::INT);
    EXPECT_EQ(cell.getAs<int>(), 2);

    const MemoryCell& varA = variableHandler->getValue("a");
    auto retrievedVarA = varA.getAs<int>();

    if (retrievedVarA == std::nullopt) {
        FAIL() << "Returned variable isn't at expected type. Current Type: " << static_cast<int>(varA.getType()) << std::endl;
    }
    EXPECT_EQ(expectedValue, retrievedVarA);
}
