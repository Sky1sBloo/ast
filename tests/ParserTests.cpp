#include "FunctionContainer.hpp"
#include "Parser.hpp"
#include "ProgramMemory.hpp"
#include "Tokenizer.hpp"
#include "VariableHandler.hpp"
#include <gtest/gtest.h>

TEST(PARSE_TESTS, VARIABLE_SAVING)
{
    std::shared_ptr<ProgramMemory> memory = std::make_shared<ProgramMemory>();
    std::shared_ptr<VariableHandler> variableHandler = std::make_shared<VariableHandler>(memory);
    std::shared_ptr<FunctionContainer> functionContainer = std::make_shared<FunctionContainer>(variableHandler);
    std::string source = "a = 5;";
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
