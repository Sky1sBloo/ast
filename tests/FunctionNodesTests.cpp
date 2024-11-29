#include <gtest/gtest.h>
#include "ParseNodes.hpp"

TEST(FUNCTION_NODES_TEST, FUNCTION_EXPR_TEST)
{
    std::shared_ptr<ProgramMemory> memory = std::make_shared<ProgramMemory>();
    std::shared_ptr<VariableHandler> varHandler = std::make_shared<VariableHandler>(memory);
    const std::string identifier = "testVar";
    int value = 5;
    int secondValue = 10;
    int returnValue = 7;

    FunctionExpr functionExpr("testFunc", varHandler);
    auto varExpr = std::make_unique<InitializationExpr>(identifier, std::make_unique<LiteralExpr>(std::to_string(value)), varHandler);
    auto assignExpr = std::make_unique<AssignExpr>(identifier, std::make_unique<LiteralExpr>(std::to_string(secondValue)), varHandler);
    auto returnLiteral = std::make_unique<LiteralExpr>(std::to_string(returnValue));

    functionExpr.insertExpr(std::make_unique<Expr>(std::move(varExpr)));
    functionExpr.insertExpr(std::make_unique<Expr>(std::move(assignExpr)));
    functionExpr.insertExpr(std::make_unique<Expr>(std::move(returnLiteral)));

    EXPECT_NO_THROW({
        int retrievedValue = functionExpr.getValue().getAs<int>().value();
        EXPECT_EQ(retrievedValue, returnValue);
        int retrievedVariableValue = varHandler->getValue(identifier).getAs<int>().value();
        EXPECT_EQ(retrievedVariableValue, secondValue);
    });
}

TEST(FUNCTION_NODES_TEST, FUNCTION_NON_RETURN_TEST)
{
    std::shared_ptr<ProgramMemory> memory = std::make_shared<ProgramMemory>();
    std::shared_ptr<VariableHandler> varHandler = std::make_shared<VariableHandler>(memory);
    const std::string identifier = "testVar";
    int value = 5;
    int secondValue = 10;
    int returnValue = 7;

    FunctionExpr functionExpr("testFunc", varHandler);
    auto varExpr = std::make_unique<InitializationExpr>(identifier, std::make_unique<LiteralExpr>(std::to_string(value)), varHandler);
    auto assignExpr = std::make_unique<AssignExpr>(identifier, std::make_unique<LiteralExpr>(std::to_string(secondValue)), varHandler);

    functionExpr.insertExpr(std::make_unique<Expr>(std::move(varExpr)));
    functionExpr.insertExpr(std::make_unique<Expr>(std::move(assignExpr)));

    EXPECT_THROW({ 
        int retrievedValue = functionExpr.getValue().getAs<int>().value();
        int retrievedVariableValue = varHandler->getValue(identifier).getAs<int>().value();
        EXPECT_EQ(retrievedVariableValue, secondValue); }, std::runtime_error);
}

TEST(FUNCTION_NODES_TEST, TERMINAL_FUNCTION_TEST)
{
    std::shared_ptr<ProgramMemory> memory = std::make_shared<ProgramMemory>();
    std::shared_ptr<VariableHandler> varHandler = std::make_shared<VariableHandler>(memory);
    const std::string identifier = "testVar";
    int value = 5;
    int secondValue = 10;

    TerminalFunctionExpr functionExpr("testFunc");
    auto varExpr = std::make_unique<InitializationExpr>(identifier, std::make_unique<LiteralExpr>(std::to_string(value)), varHandler);
    auto assignExpr = std::make_unique<AssignExpr>(identifier, std::make_unique<LiteralExpr>(std::to_string(secondValue)), varHandler);

    functionExpr.insertExpr(std::make_unique<Expr>(std::move(varExpr)));
    functionExpr.insertExpr(std::make_unique<Expr>(std::move(assignExpr)));
    functionExpr.performAction();

    EXPECT_NO_THROW({
        int retrievedVariableValue = varHandler->getValue(identifier).getAs<int>().value();
        EXPECT_EQ(retrievedVariableValue, secondValue);
    });
}

TEST(FUNCTION_NODES_TEST, TERMINAL_FUNCTION_RETRUN_TEST)
{
    std::shared_ptr<ProgramMemory> memory = std::make_shared<ProgramMemory>();
    std::shared_ptr<VariableHandler> varHandler = std::make_shared<VariableHandler>(memory);
    const std::string identifier = "testVar";
    int value = 5;
    int secondValue = 10;
    int returnValue = 7;

    TerminalFunctionExpr functionExpr("testFunc");
    auto varExpr = std::make_unique<InitializationExpr>(identifier, std::make_unique<LiteralExpr>(std::to_string(value)), varHandler);
    auto assignExpr = std::make_unique<AssignExpr>(identifier, std::make_unique<LiteralExpr>(std::to_string(secondValue)), varHandler);
    auto returnLiteral = std::make_unique<LiteralExpr>(std::to_string(returnValue));

    functionExpr.insertExpr(std::make_unique<Expr>(std::move(varExpr)));
    functionExpr.insertExpr(std::make_unique<Expr>(std::move(assignExpr)));
    functionExpr.insertExpr(std::make_unique<Expr>(std::move(returnLiteral)));

    EXPECT_THROW({
        functionExpr.performAction();
        int retrievedVariableValue = varHandler->getValue(identifier).getAs<int>().value();
        EXPECT_EQ(retrievedVariableValue, secondValue);
    }, std::runtime_error);
}
