#include "ParseNodes.hpp"

FunctionExpr::FunctionExpr(const std::string& id, std::shared_ptr<VariableHandler> handler)
    : _id(id)
    , _statements()
    , _handler(handler)
    , _params(nullptr)
{
}

FunctionExpr::FunctionExpr(const std::string& id, std::shared_ptr<VariableHandler> handler, std::unique_ptr<FunctionParameterContainer> params)
    : _id(id)
    , _statements()
    , _handler(handler)
    , _params(std::move(params))
{
}

void FunctionExpr::insertExpr(std::unique_ptr<Expr> expr)
{
    _statements.push_back(std::move(expr));
}

void FunctionExpr::insertExpr(std::unique_ptr<ReturnableExpr> expr)
{
    _statements.push_back(std::make_unique<Expr>(std::move(expr)));
}

void FunctionExpr::insertExpr(std::unique_ptr<TerminalExpr> expr)
{
    _statements.push_back(std::make_unique<Expr>(std::move(expr)));
}

const MemoryCell& FunctionExpr::getValue() const
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
