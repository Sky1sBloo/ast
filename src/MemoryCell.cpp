#include "MemoryCell.hpp"
#include <cctype>
#include <cmath>

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
