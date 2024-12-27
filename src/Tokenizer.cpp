#include "Tokenizer.hpp"
#include <algorithm>
#include <cctype>
#include <stdexcept>
#include <string>

void Tokenizer::pushToken(Token::SubTypes type, Token::SubTypes& prevType, std::string& tokenStr)
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
    Token::SubTypes prevType = Token::SubTypes::INVALID;
    bool prevIsDelimeter = false;

    for (char c : sourceCode) {
        if (c == ' ') {
            Token::SubTypes type = identifyType(tokenStr);
            if (type != Token::SubTypes::INVALID) {
                pushToken(type, prevType, tokenStr);
            }
            continue;
        }

        if (c == _terminationChar) {
            if (!tokenStr.empty()) {
                Token::SubTypes type = identifyType(tokenStr);
                pushToken(type, prevType, tokenStr);
            }
            tokenStr = ";";
            pushToken(Token::SubTypes::STATEMENT_TERMINATE, prevType, tokenStr);
            continue;
        }
        // TODO: Add ruleset for when to terminate
        switch (prevType) {
        case Token::SubTypes::ANY:
            throw std::runtime_error("Tried to tokenize an ANY subtype");
        case Token::SubTypes::LITERAL:
        case Token::SubTypes::KEYWORD:
        case Token::SubTypes::IDENTIFIER:
            if (std::ranges::find(_delimeters, c) != _delimeters.end() || isBrace(std::to_string(c)) || isOperation(std::to_string(c))) {
                Token::SubTypes type = identifyType(tokenStr);
                pushToken(type, prevType, tokenStr);
            }
            break;
        case Token::SubTypes::OPERATOR:
        case Token::SubTypes::BRACE:
        case Token::SubTypes::ASSIGN:
        case Token::SubTypes::INVALID:
        case Token::SubTypes::STATEMENT_TERMINATE:
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

Token::SubTypes Tokenizer::identifyType(const std::string& word)
{
    if (isKeyword(word)) {
        return Token::SubTypes::KEYWORD;
    }
    if (isOperation(word)) {
        return Token::SubTypes::OPERATOR;
    }
    if (isBrace(word)) {
        return Token::SubTypes::BRACE;
    }
    if (isAssignment(word)) {
        return Token::SubTypes::ASSIGN;
    }
    if (isLiteral(word)) {
        return Token::SubTypes::LITERAL;
    }
    if (isIdentifier(word)) {
        return Token::SubTypes::IDENTIFIER;
    }

    return Token::SubTypes::INVALID;
};

bool Tokenizer::isKeyword(const std::string& word) const
{
    return _keywordRuleset.contains(word);
}

bool Tokenizer::isOperation(const std::string& word) const
{
    if (word.length() != 1) {
        return false;
    }
    return _operationRuleset.contains(word[0]);
}

bool Tokenizer::isBrace(const std::string& word) const
{
    if (word.length() != 1) {
        return false;
    }
    return _braceRuleset.contains(word[0]);
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

    bool isString = !word.empty() && word.front() == word.back() && _stringLiteralRuleset.contains(word.front());
    if (isString) {
        return true;
    }

    if (_booleanLiteralRuleset.contains(word)) {
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
