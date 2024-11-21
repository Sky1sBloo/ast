#include "ParseNodes.hpp"

FunctionExpr::FunctionExpr(const std::string& id, std::vector<std::unique_ptr<Expr>>& statements)
    : _id(id)
    , _statements(statements)
{
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
                [&returnable](const std::unique_ptr<ReturnableExpr>& returnableExpr) {
                    return true;
                } },
            statement->getVariant());

        if (foundReturnStatement) {
            return statement->getAs<ReturnableExpr>().getValue();
        }
    }
    throw std::runtime_error("Function Expression doesn't have returnable expression");
}
