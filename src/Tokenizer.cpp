#include "Tokenizer.hpp"
#include <algorithm>
#include <cctype>
#include <string>

Tokenizer::Tokenizer(std::stringstream& sourceCode)
{
    std::string word;
    while (sourceCode >> word) {
        // To avoid checking terminate character on identifying type
        bool containsTermination = hasTerminateChar(word);
        if (containsTermination) {
            word.pop_back();
        }

        if (!word.empty()) {
            Token::Types type = identitfyType(word);
            _tokens.push_back(Token(type, word));
        }

        if (containsTermination) {
            std::string terminationStr(1, _terminationChar);
            _tokens.push_back(Token(Token::Types::STATEMENT_TERMINATE, terminationStr));
        }
    }
}

bool Tokenizer::hasTerminateChar(const std::string& word) const
{
    return (word.back() == _terminationChar);
}

Token::Types Tokenizer::identitfyType(const std::string& word)
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
    return std::ranges::find(_operationRuleset, word) != _operationRuleset.end();
}

bool Tokenizer::isAssignment(const std::string& word) const
{
    return (word == _assignmentRuleset);
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
    for (const char c : word) {
        if (std::ranges::find(_identifierInvalidCharacters, c) != _identifierInvalidCharacters.end()) {
            return false;
        }
    }
    return true;
}
