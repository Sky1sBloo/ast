#pragma once

#include <algorithm>
#include <array>
#include <optional>
#include <sstream>
#include <unordered_map>
#include <vector>

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

    constexpr bool isTerminal() const
    {
        return std::ranges::find(terminalTokens, type) != terminalTokens.end();
    }

    constexpr bool isValue() const
    {
        return std::ranges::find(valueTokens, type) != terminalTokens.end();
    }

    /**
     * Gets the precedence of token
     */
    std::optional<int> getTerminalPrecedence() const
    {
        if (precedenceTokens.contains(type)) {
            return precedenceTokens.at(type);
        }
        return std::nullopt;
    }

private:
    /**
     * Lists all tokens that are action
     */
    constexpr static std::array<Types, 3> terminalTokens = {
        Types::ASSIGN,
        Types::KEYWORD,
        Types::OPERATOR
    };

    constexpr static std::array<Types, 2> valueTokens = {
        Types::IDENTIFIER,
        Types::LITERAL
    };

    /**
     * Precedence of tokens
     * Higher number means earlier precedence
     */
    inline const static std::unordered_map<Types, int> precedenceTokens = {
        { Types::ASSIGN, 0 },
        { Types::KEYWORD, 1 },
        { Types::OPERATOR, 2 },
    };
};

class Tokenizer {
public:
    Tokenizer(std::stringstream& sourceCode);

    const std::vector<Token>& getTokens() const { return _tokens; }

private:
    std::vector<Token> _tokens;

    Token::Types identitfyType(const std::string& word);
    /**
     * Checks the edge of string if it has termination character
     */
    bool hasTerminateChar(const std::string& word) const;

    // The following functions checks by ruleset
    bool isKeyword(const std::string& word) const;
    bool isOperation(const std::string& word) const;
    bool isAssignment(const std::string& word) const;
    bool isLiteral(const std::string& word) const;
    bool isIdentifier(const std::string& word) const;

private:
    // RULESETS
    constexpr static std::array<std::string, 1> _keywordRuleset = {
        "var"
    };
    constexpr static std::array<std::string, 4> _operationRuleset = {
        "+", "-", "/", "*"
    };
    constexpr static std::array<char, 2> _stringLiteralRuleset = {
        '\'', '\"'
    };
    constexpr static std::array<std::string, 4> _booleanLiteralRuleset = {
        "true", "True", "false", "False"
    };
    constexpr static std::array<char, 8> _identifierInvalidCharacters = {
        '\"', '\'', ';', '+', '-', '*', '/', '='
    };

    constexpr static std::string _assignmentRuleset = "=";
    constexpr static char _terminationChar = ';';
};
