#include "FunctionContainer.hpp"
#include "FunctionDefinition.hpp"
#include "ParseNodes.hpp"
#include <gtest/gtest.h>

TEST(FUNCTION_TEST, FUNCTION_RETURN_TEST)
{
    std::shared_ptr<ProgramMemory> memory = std::make_shared<ProgramMemory>();
    std::shared_ptr<VariableHandler> varHandler = std::make_shared<VariableHandler>(memory);
    std::shared_ptr<FunctionContainer> functionHandler = std::make_shared<FunctionContainer>(varHandler);

    const std::string varIdentifier = "testVar";
    int varSetValue = 5;
    int returnValue = 7;
    const std::string funcIdentifier = "testFunc";

    auto functionExpr = std::make_unique<FunctionDefinition>(funcIdentifier, varHandler);
    auto varExpr = std::make_unique<InitializationExpr>(varIdentifier, varHandler);
    auto assignExpr = std::make_unique<AssignExpr>(varIdentifier, std::make_unique<LiteralExpr>(std::to_string(varSetValue)), varHandler);
    auto returnLiteral = std::make_unique<LiteralExpr>(std::to_string(returnValue));

    functionExpr->insertExpr(std::move(assignExpr));
    functionExpr->insertExpr(std::move(returnLiteral));

    functionHandler->insertFunction(std::move(functionExpr));
    auto functionCallExpr = std::make_unique<FunctionCallExpr>(funcIdentifier, functionHandler, varHandler);
    EXPECT_NO_THROW({
        varExpr->performAction();
        int retrievedValue = functionCallExpr->getValue().getAs<int>().value();
        EXPECT_EQ(returnValue, retrievedValue);
        int varRetrieved = varHandler->getValue(varIdentifier).getAs<int>().value();
        EXPECT_EQ(varRetrieved, varSetValue);
    });
}

TEST(FUNCTION_TEST, FUNCTION_PARAM_TEST)
{
    std::shared_ptr<ProgramMemory> memory = std::make_shared<ProgramMemory>();
    std::shared_ptr<VariableHandler> varHandler = std::make_shared<VariableHandler>(memory);
    std::shared_ptr<FunctionContainer> functionHandler = std::make_shared<FunctionContainer>(varHandler);

    const std::string varIdentifier = "testVar";
    int varSetValue = 5;
    int returnValue = 7;
    const std::string funcIdentifier = "testFunc";

    std::vector<std::string> funcParams = { "param_1", "param_2" };
    auto functionExpr = std::make_unique<FunctionDefinition>(funcIdentifier, varHandler, funcParams);
    auto assignExpr = std::make_unique<InitializationExpr>(varIdentifier, std::make_unique<LiteralExpr>(std::to_string(varSetValue)), varHandler);
    auto varExpr = std::make_unique<AssignExpr>(varIdentifier, std::make_unique<VariableIdentifier>("param_1", varHandler), varHandler);
    auto returnLiteral = std::make_unique<VariableIdentifier>("param_2", varHandler);

    functionExpr->insertExpr(std::move(varExpr));
    functionExpr->insertExpr(std::move(returnLiteral));

    functionHandler->insertFunction(std::move(functionExpr));
    auto functionCallExpr = std::make_unique<FunctionCallExpr>(funcIdentifier, functionHandler, varHandler);
    functionCallExpr->insertParam(std::make_unique<LiteralExpr>(std::to_string(varSetValue)));
    functionCallExpr->insertParam(std::make_unique<LiteralExpr>(std::to_string(returnValue)));

    EXPECT_NO_THROW({
        assignExpr->performAction();
        int retrievedValue = functionCallExpr->getValue().getAs<int>().value();
        EXPECT_EQ(returnValue, retrievedValue);
        int varRetrieved = varHandler->getValue(varIdentifier).getAs<int>().value();
        EXPECT_EQ(varRetrieved, varSetValue);
    });
}

