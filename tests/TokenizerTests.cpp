#include <array>
#include <gtest/gtest.h>
#include <ranges>
#include <string>

#include "Token.hpp"
#include "Tokenizer.hpp"

TEST(TOKENIZER_TESTS, READING)
{
    std::string source = "var a = 5; var b = 2.0 + 5.0;\nvar c = \"fifty\";\n";
    const std::array<Token::SubTypes, 17> expectedSubTypes = {
        Token::SubTypes::KEYWORD,
        Token::SubTypes::IDENTIFIER,
        Token::SubTypes::ASSIGN,
        Token::SubTypes::LITERAL,
        Token::SubTypes::STATEMENT_TERMINATE,
        Token::SubTypes::KEYWORD,
        Token::SubTypes::IDENTIFIER,
        Token::SubTypes::ASSIGN,
        Token::SubTypes::LITERAL,
        Token::SubTypes::OPERATOR,
        Token::SubTypes::LITERAL,
        Token::SubTypes::STATEMENT_TERMINATE,
        Token::SubTypes::KEYWORD,
        Token::SubTypes::IDENTIFIER,
        Token::SubTypes::ASSIGN,
        Token::SubTypes::LITERAL,
        Token::SubTypes::STATEMENT_TERMINATE
    };

    Tokenizer tokenizer(source);

    EXPECT_EQ(tokenizer.getTokens().size(), expectedSubTypes.size());
    for (const auto& [token, expectedToken] : std::views::zip(tokenizer.getTokens(), expectedSubTypes)) {
        EXPECT_EQ(token.getSubType(), expectedToken);
    }
}

TEST(TOKENIZER_TESTS, FUNCTION)
{
    std::string source = "func test() {}";
    const std::array<Token::SubTypes, 17> expectedSubTypes = {
        Token::SubTypes::KEYWORD,
        Token::SubTypes::IDENTIFIER,
        Token::SubTypes::BRACE,
        Token::SubTypes::BRACE,
        Token::SubTypes::BRACE,
        Token::SubTypes::BRACE
    };

    Tokenizer tokenizer(source);

    EXPECT_EQ(tokenizer.getTokens().size(), expectedSubTypes.size());
    for (const auto& [token, expectedToken] : std::views::zip(tokenizer.getTokens(), expectedSubTypes)) {
        EXPECT_EQ(token.getSubType(), expectedToken);
    }
}
