#pragma once

#include <sstream>
#include <vector>

enum class TokenTypes {
    LITERAL,
    KEYWORD,
    IDENTIFIER,
    VARIABLE_DECLARATION,
    ASSIGN
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
private:
    std::vector<Token> _tokens;

    TokenTypes identitfyType(const std::string& word);
};
