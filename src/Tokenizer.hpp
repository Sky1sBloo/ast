#pragma once

#include <unordered_set>
#include <string>
#include <vector>
#include "Token.hpp"

class Tokenizer {
public:
    Tokenizer(std::string& sourceCode);

    const std::vector<Token>& getTokens() { return _tokens; }

private:
    std::vector<Token> _tokens;

    Token::SubTypes identifyType(const std::string& word);
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
    inline const static std::unordered_set<std::string> _keywordRuleset = {
        "var"
    };
    inline const static std::unordered_set<char> _operationRuleset = {
        '+', '-', '/', '*'
    };
    inline const static std::unordered_set<char> _stringLiteralRuleset = {
        '\'', '\"'
    };
    inline const static std::unordered_set<std::string> _booleanLiteralRuleset = {
        "true", "True", "false", "False"
    };
    inline const static std::unordered_set<char> _identifierDelimeters = {
        '\"', '\'', ';', '+', '-', '*', '/', '=' 
    };
    inline const static std::unordered_set<char> _delimeters = {
        ' ', '\n', '\t'
    };

    const static char _assignmentRuleset = '=';
    const static char _terminationChar = ';';

    /**
     * Helper function for constructor
     * Modifies and empties tokenStr and prevType
    */
    void pushToken(Token::SubTypes type, Token::SubTypes& prevType, std::string& tokenStr);
};
