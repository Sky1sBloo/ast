#include "ParseTreeBuilder.hpp"
#include "ProgramMemory.hpp"
#include "VariableHandler.hpp"
#include "Tokenizer.hpp"

#include <gtest/gtest.h>
#include <sstream>
#include <optional>

TEST(PARSE_TREE_TESTS, VARIABLE_SAVING)
{
    std::shared_ptr<ProgramMemory> memory = std::make_shared<ProgramMemory>();
    std::shared_ptr<VariableHandler> variableHandler = std::make_shared<VariableHandler>(memory);
    std::stringstream source;
    source << "a = 5;";
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
