#pragma once

#include <algorithm>
#include <array>
#include <sstream>
#include <vector>

enum class TokenTypes {
    INVALID,
    LITERAL,
    KEYWORD,
    IDENTIFIER,
    OPERATOR,
    ASSIGN,
    STATEMENT_TERMINATE
};

struct Token {
    TokenTypes type;
    std::string value;

    Token(TokenTypes newType, const std::string& newValue)
        : type(newType)
        , value(newValue)
    {
    }

    bool isTerminal() const {
        return std::ranges::find(terminalTokens, type) != terminalTokens.end();
    }

    bool isValue() const {
        return std::ranges::find(valueTokens, type) != terminalTokens.end();
    }
private:
    /**
     * Lists all tokens that are action
     */
    constexpr static std::array<TokenTypes, 3> terminalTokens = {
        TokenTypes::ASSIGN,
        TokenTypes::KEYWORD,
        TokenTypes::OPERATOR
    };

    constexpr static std::array<TokenTypes, 2> valueTokens = {
        TokenTypes::IDENTIFIER,
        TokenTypes::LITERAL
    };
};

class Tokenizer {
public:
    Tokenizer(std::stringstream& sourceCode);

    const std::vector<Token>& getTokens() const { return _tokens; }

private:
    std::vector<Token> _tokens;

    TokenTypes identitfyType(const std::string& word);
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
