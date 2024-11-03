#pragma once

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

    constexpr static std::string _assignmentRuleset = "=";
    constexpr static char _terminationChar = ';';
};
