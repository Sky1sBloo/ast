#include "ParseNodes.hpp"

FunctionExpr::FunctionExpr(const std::string& id, std::shared_ptr<VariableHandler> handler, std::initializer_list<std::string> params)
    : _id(id)
    , _statements()
    , _params(params)
    , _handler(handler)
{
    for (const std::string& param : params) {
        _handler->allocate(param);
    }
}

FunctionExpr::~FunctionExpr()
{
    for (const std::string& param : _params) {
        _handler->deallocate(param);
    }
}

void FunctionExpr::insertExpr(std::unique_ptr<Expr> expr)
{
    _statements.push_back(std::move(expr));
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
