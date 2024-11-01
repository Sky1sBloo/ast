#include "ParseNodes.hpp"

LiteralExpr::LiteralExpr(DataType type, const std::string& value)
    : _type(type)
    , _value(value)
{
}
