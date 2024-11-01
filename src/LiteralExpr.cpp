#include "ParseNodes.hpp"

LiteralExpr::LiteralExpr(DataType newDataType, const std::string& newValue)
    : type(newDataType)
    , value(newValue)
{
}
