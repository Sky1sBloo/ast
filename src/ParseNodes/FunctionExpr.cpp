#include "ParseNodes.hpp"

FunctionExpr::FunctionExpr(const std::string& id, std::vector<std::unique_ptr<Expr>>& statements)
    : _id(id)
    , _statements(statements)
{
}

const MemoryCell& FunctionExpr::getValue() const
{
}
