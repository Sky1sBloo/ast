#include "Tokenizer.hpp"
#include <algorithm>
#include <cctype>
#include <string>

void Tokenizer::pushToken(Token::Types type, Token::Types& prevType, std::string& tokenStr)
{
    if (tokenStr.empty()) {
        return;
    }
    _tokens.emplace_back(type, tokenStr);
    prevType = type;
    tokenStr.clear();
}

Tokenizer::Tokenizer(std::string& sourceCode)
{
    std::string tokenStr;
    Token::Types prevType = Token::Types::INVALID;
    bool prevIsDelimeter = false;

    for (char c : sourceCode) {
        if (c == ' ') {
            Token::Types type = identifyType(tokenStr);
            pushToken(type, prevType, tokenStr);
            continue;
        }

        if (c == _terminationChar) {
            if (!tokenStr.empty()) {
                Token::Types type = identifyType(tokenStr);
                pushToken(type, prevType, tokenStr);
            }
            tokenStr = ";";
            pushToken(Token::Types::STATEMENT_TERMINATE, prevType, tokenStr);
            continue;
        }
        // TODO: Add ruleset for when to terminate
        switch (prevType) {
        case Token::Types::LITERAL:
        case Token::Types::KEYWORD:
        case Token::Types::IDENTIFIER:
            if (std::ranges::find(_delimeters, c) != _delimeters.end()) {
                Token::Types type = identifyType(tokenStr);
                pushToken(type, prevType, tokenStr);
            }
            break;
        case Token::Types::OPERATOR:
        case Token::Types::ASSIGN:
        case Token::Types::INVALID:
        case Token::Types::STATEMENT_TERMINATE:
            break;
        };

        if (std::ranges::find(_delimeters, c) == _delimeters.end()) {
            tokenStr += c;
        }
    }
}

bool Tokenizer::hasTerminateChar(const std::string& word) const
{
    return (word.back() == _terminationChar);
}

Token::Types Tokenizer::identifyType(const std::string& word)
{
    if (isKeyword(word)) {
        return Token::Types::KEYWORD;
    }
    if (isOperation(word)) {
        return Token::Types::OPERATOR;
    }
    if (isAssignment(word)) {
        return Token::Types::ASSIGN;
    }
    if (isLiteral(word)) {
        return Token::Types::LITERAL;
    }
    if (isIdentifier(word)) {
        return Token::Types::IDENTIFIER;
    }

    return Token::Types::INVALID;
};

bool Tokenizer::isKeyword(const std::string& word) const
{
    return std::ranges::find(_keywordRuleset, word) != _keywordRuleset.end();
}

bool Tokenizer::isOperation(const std::string& word) const
{
    if (word.length() != 1) {
        return false;
    }
    return std::ranges::find(_operationRuleset, word[0]) != _operationRuleset.end();
}

bool Tokenizer::isAssignment(const std::string& word) const
{
    if (word.length() != 1) {
        return false;
    }
    return (word[0] == _assignmentRuleset);
}

bool Tokenizer::isLiteral(const std::string& word) const
{
    bool isNumerical = std::ranges::all_of(word, [](char c) { return (std::isdigit(c) || c == '.'); });
    if (isNumerical) {
        return true;
    }

    bool isString = word.front() == word.back() && std::ranges::find(_stringLiteralRuleset, word.front()) != _stringLiteralRuleset.end();
    if (isString) {
        return true;
    }

    bool isBoolean = std::ranges::find(_booleanLiteralRuleset, word) != _booleanLiteralRuleset.end();
    if (isBoolean) {
        return true;
    }

    return false;
}

bool Tokenizer::isIdentifier(const std::string& word) const
{
    // Don't need this since I check for this in the constructor
    /*
    for (const char c : word) {
        if (std::ranges::find(_identifierDelimeters, c) != _identifierDelimeters.end()) {
            return false;
        }
    } */
    return true;
}
