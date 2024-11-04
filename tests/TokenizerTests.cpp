#include <array>
#include <gtest/gtest.h>
#include <ranges>
#include <sstream>

#include "Tokenizer.hpp"

TEST(TOKENIZER_TESTS, READING)
{
    std::stringstream source;
    source << "var a = 5; var b = 2.0 + 5.0;\nvar c = \"fifty\";\n";
    const std::array<TokenTypes, 17> expectedTypes = {
        TokenTypes::KEYWORD,
        TokenTypes::IDENTIFIER,
        TokenTypes::ASSIGN,
        TokenTypes::LITERAL,
        TokenTypes::STATEMENT_TERMINATE,
        TokenTypes::KEYWORD,
        TokenTypes::IDENTIFIER,
        TokenTypes::ASSIGN,
        TokenTypes::LITERAL,
        TokenTypes::OPERATOR,
        TokenTypes::LITERAL,
        TokenTypes::STATEMENT_TERMINATE,
        TokenTypes::KEYWORD,
        TokenTypes::IDENTIFIER,
        TokenTypes::ASSIGN,
        TokenTypes::LITERAL,
        TokenTypes::STATEMENT_TERMINATE
    };

    Tokenizer tokenizer(source);

    for (auto [token, expectedToken] : std::views::zip(tokenizer.getTokens(), expectedTypes)) {
        EXPECT_EQ(token.type, expectedToken);
    }
}
