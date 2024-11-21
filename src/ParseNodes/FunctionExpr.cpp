#include "ParseNodes.hpp"

FunctionExpr::FunctionExpr(const std::string& id)
    : _id(id)
    , _statements()
{
}

void FunctionExpr::insertStatement(std::unique_ptr<Expr> statement)
{
    _statements.push_back(std::move(statement));
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
