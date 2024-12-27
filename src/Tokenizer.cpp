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
        if (_delimeters.contains(c) || c == _terminationChar) {
            Token::SubTypes type = identifyType(tokenStr);
            if (type == Token::SubTypes::INVALID) {
                throw std::invalid_argument("Cannot identify token");
            }
            if (type == Token::SubTypes::ANY) {
                throw std::invalid_argument("Tried to tokenize any subtype");
            }
            pushToken(type, prevType, tokenStr);

            if (c == _terminationChar) {
                tokenStr = std::string(1, _terminationChar);
                pushToken(Token::SubTypes::STATEMENT_TERMINATE, prevType, tokenStr);
            }
            continue;
        }

        if (_delimeters.contains(c) || _braceRuleset.contains(c) || _operationRuleset.contains(c) || _assignmentRuleset == c) {
            Token::SubTypes type = identifyType(tokenStr);
            pushToken(type, prevType, tokenStr);
            tokenStr += c;
            type = identifyType(tokenStr);
            pushToken(type, prevType, tokenStr);
            continue;
        }

        tokenStr += c;
    }

    if (!tokenStr.empty()) {
        Token::SubTypes type = identifyType(tokenStr);
        if (type != Token::SubTypes::INVALID) {
            pushToken(type, prevType, tokenStr);
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
