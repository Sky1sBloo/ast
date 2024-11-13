#pragma once

#include <array>
#include <string>
#include <vector>
#include "Token.hpp"

class Tokenizer {
public:
    Tokenizer(std::string& sourceCode);

    const std::vector<TokenContainer>& getTokens() { return _tokens; }

private:
    std::vector<TokenContainer> _tokens;

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
