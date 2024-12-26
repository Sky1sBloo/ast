#include "FunctionDefinition.hpp"

FunctionDefinition::FunctionDefinition(const std::string& id)
    : _id(id)
    , _statements()
    , _params()
{
}

FunctionDefinition::FunctionDefinition(const std::string& id, const std::vector<std::string>& params)
    : _id(id)
    , _statements()
    , _params(params)
{
}

FunctionDefinition::~FunctionDefinition()
{
}

void FunctionDefinition::insertExpr(std::unique_ptr<Expr> expr)
{
    _statements.push_back(std::move(expr));
}

void FunctionDefinition::insertExpr(std::unique_ptr<ReturnableExpr> expr)
{
    _statements.push_back(std::make_unique<Expr>(std::move(expr)));
}

void FunctionDefinition::insertExpr(std::unique_ptr<TerminalExpr> expr)
{
    _statements.push_back(std::make_unique<Expr>(std::move(expr)));
}

const MemoryCell& FunctionDefinition::getValue()
{
    const MemoryCell* returnable = nullptr;
    for (auto& statement : _statements) {
        bool foundReturnStatement = std::visit(
            ExprVariantVisitor {
                [](const std::unique_ptr<TerminalExpr>& terminalExpr) {
                    terminalExpr->performAction();
                    return false;
                },
                [](const std::unique_ptr<ReturnableExpr>& returnableExpr) {
                    return true;
                } },
            statement->getVariant());

        if (foundReturnStatement) {
            return statement->getAs<ReturnableExpr>().getValue();
        }
    }
    throw std::runtime_error("Function Expression doesn't have returnable expression");
}
