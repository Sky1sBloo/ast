#pragma once
#include <array>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <variant>

/**
 * Class containing token variant
 */
class TokenContainer;

/**
 * Base class for tokens
 */
class Token {
public:
    enum class Types {
        INVALID,
        LITERAL,
        KEYWORD,
        IDENTIFIER,
        OPERATOR,
        ASSIGN,
        STATEMENT_TERMINATE
    };

    Types type;
    std::string value;

    Token(Types newType, const std::string& newValue)
        : type(newType)
        , value(newValue)
    {
    }
};

/**
 * Token representing a value or returnable
 */
class ValueToken : public Token {
public:
    ValueToken(Types newType, const std::string& newValue)
        : Token(newType, newValue)
    {
        if (!isValidType()) {
            throw std::invalid_argument("ValueToken inherits invalid type");
        }
    }

private:
    constexpr static std::array<Types, 2> valueTypes = {
        Types::IDENTIFIER,
        Types::LITERAL
    };

    constexpr bool isValidType()
    {
        for (Types validType : valueTypes) {
            if (type == validType) {
                return true;
            }
        }
        return false;
    }
};

/**
 * Token representing a terminal or non returnable
 */
class TerminalToken : public Token {
    TerminalToken(Types newType, const std::string& newValue)
        : Token(newType, newValue)
    {
        if (!isValidType()) {
            throw std::invalid_argument("Terminal Token inherits invalid type");
        }
    }

    int getPrecedence() const
    {
        return precedenceTokens.at(type);
    }

private:
    constexpr static std::array<Types, 3> terminalTypes = {
        Types::ASSIGN,
        Types::KEYWORD,
        Types::OPERATOR
    };

    inline const static std::unordered_map<Types, int> precedenceTokens = {
        { Types::ASSIGN, 0 },
        { Types::KEYWORD, 1 },
        { Types::OPERATOR, 2 },
    };

    constexpr bool isValidType()
    {
        for (Types validType : terminalTypes) {
            if (type == validType) {
                return true;
            }
        }
        return false;
    }
};

class TokenContainer {
public:
    std::variant<ValueToken, TerminalToken> token;
};
