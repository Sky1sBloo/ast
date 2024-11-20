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
        if (!isValidType(type)) {
            throw std::invalid_argument("ValueToken inherits invalid type");
        }
    }

    constexpr static bool isValidType(Types typeCheck) noexcept
    {
        for (Types validType : valueTypes) {
            if (typeCheck == validType) {
                return true;
            }
        }
        return false;
    }

private:
    constexpr static std::array<Types, 2> valueTypes = {
        Types::IDENTIFIER,
        Types::LITERAL
    };
};

/**
 * Token representing a terminal or non returnable
 */
class TerminalToken : public Token {
public:
    TerminalToken(Types newType, const std::string& newValue)
        : Token(newType, newValue)
    {
        if (!isValidType(newType)) {
            throw std::invalid_argument("Terminal Token inherits invalid type");
        }
    }

    int getPrecedence() const
    {
        return precedenceTokens.at(type);
    }

    constexpr static bool isValidType(Types typeCheck) noexcept
    {
        for (Types validType : terminalTypes) {
            if (typeCheck == validType) {
                return true;
            }
        }
        return false;
    }

private:
    constexpr static std::array<Types, 4> terminalTypes = {
        Types::ASSIGN,
        Types::KEYWORD,
        Types::OPERATOR,
        Types::STATEMENT_TERMINATE
    };

    inline const static std::unordered_map<Types, int> precedenceTokens = {
        { Types::ASSIGN, 0 },
        { Types::KEYWORD, 1 },
        { Types::OPERATOR, 2 },
    { Types::STATEMENT_TERMINATE, -1}
    };
};

class TokenContainer {
public:
    TokenContainer(Token::Types newType, const std::string& newValue = "")
        : _token(createTokenVariant(newType, newValue))
    {
    }

    using TokenVariant = std::variant<ValueToken, TerminalToken>;
    const TokenVariant& getToken() const { return _token; }

private:
    constexpr TokenVariant createTokenVariant(Token::Types newType, const std::string& newValue) const
    {
        if (ValueToken::isValidType(newType)) {
            return ValueToken(newType, newValue);
        } else if (TerminalToken::isValidType(newType)) {
            return TerminalToken(newType, newValue);
        } else {
            throw std::invalid_argument("Token container cant identifiy type");
        }
    }

    TokenVariant _token;
};
