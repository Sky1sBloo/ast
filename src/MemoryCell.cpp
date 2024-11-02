#include "MemoryCell.hpp"
#include <cctype>
#include <cmath>
#include <cstring>

MemoryCell::MemoryCell(const std::string& value)
{
    if (strToFloat(value)) {
        return;
    }
}

bool MemoryCell::strToFloat(const std::string& value)
{
    float output = 0;
    float decimalPlaceMultiplier = 0.1f;
    bool passedDecimal = false;

    for (char c : value) {
        if (std::isdigit(c)) {
            int digit = c - '0';
            if (!passedDecimal) {
                output *= 10;
                output += digit;
            } else {
                output += digit * decimalPlaceMultiplier;
                decimalPlaceMultiplier *= 0.1f;
            }
        } else if (c == '.') {
            passedDecimal = true;
        } else {
            return false;
        }
    }

    _value = output;
    return true;
}

bool MemoryCell::strToBool(const std::string& value)
{
    if (value == "True" || value == "true") {
        _value = true;
        return true;
    }

    if (value == "False" || value == "false") {
        _value = false;
        return true;
    }

    return false;
}
