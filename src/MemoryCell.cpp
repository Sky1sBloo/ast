#include "MemoryCell.hpp"
#include <cctype>
#include <cmath>
#include <cstring>

MemoryCell::MemoryCell(const std::string& value)
{
    typeDeducer(value);
}

MemoryCell::MemoryCell(const MemoryCell& other) :
    _value(other._value)
{
}

MemoryCell& MemoryCell::operator=(const MemoryCell& other)
{
    _value = other._value;
    return *this;
}

void MemoryCell::set(const std::string& value)
{
    typeDeducer(value);
}

DataType MemoryCell::getType() const
{
    return std::visit([](auto&& value) -> DataType {
        using T = std::decay_t<decltype(value)>;
        if constexpr (std::is_same_v<T, int>) {
            return DataType::INT;
        }
        if constexpr (std::is_same_v<T, float>) {
            return DataType::FLOAT;
        }
        if constexpr (std::is_same_v<T, bool>) {
            return DataType::BOOL;
        }
        if constexpr (std::is_same_v<T, std::string>) {
            return DataType::STRING;
        }
        return DataType::NULL_TYPE;
    },
        _value);
};

void MemoryCell::typeDeducer(const std::string& value)
{
    if (strToInt(value))
        return;
    if (strToFloat(value))
        return;
    if (strToBool(value))
        return;
    if (value == "NULL") {
        _value = std::monostate();
        return;
    }
    if (value != "") {
        _value = value;
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

bool MemoryCell::strToInt(const std::string& value)
{
    int output = 0;
    for (char c : value) {
        if (std::isdigit(c)) {
            output *= 10;
            output += c - '0';
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
