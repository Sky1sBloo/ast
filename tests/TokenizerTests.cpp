#include <array>
#include <gtest/gtest.h>
#include <ranges>
#include <sstream>
#include <variant>

#include "Token.hpp"
#include "Tokenizer.hpp"

TEST(TOKENIZER_TESTS, READING)
{
    std::stringstream source;
    source << "var a = 5; var b = 2.0 + 5.0;\nvar c = \"fifty\";\n";
    const std::array<Token::Types, 17> expectedTypes = {
        Token::Types::KEYWORD,
        Token::Types::IDENTIFIER,
        Token::Types::ASSIGN,
        Token::Types::LITERAL,
        Token::Types::STATEMENT_TERMINATE,
        Token::Types::KEYWORD,
        Token::Types::IDENTIFIER,
        Token::Types::ASSIGN,
        Token::Types::LITERAL,
        Token::Types::OPERATOR,
        Token::Types::LITERAL,
        Token::Types::STATEMENT_TERMINATE,
        Token::Types::KEYWORD,
        Token::Types::IDENTIFIER,
        Token::Types::ASSIGN,
        Token::Types::LITERAL,
        Token::Types::STATEMENT_TERMINATE
    };

    Tokenizer tokenizer(source);

    for (auto [tokenContainer, expectedToken] : std::views::zip(tokenizer.getTokens(), expectedTypes)) {
        std::visit([&expectedToken](const auto& token) {
            EXPECT_EQ(token.type, expectedToken);
        },
            tokenContainer.getToken());
    }
}
