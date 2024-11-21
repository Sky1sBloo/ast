#pragma once
#include "ParseNodes.hpp"
#include "Token.hpp"
#include "VariableHandler.hpp"

#include <array>
#include <memory>
#include <queue>

class ParseTreeBuilder {
public:
    ParseTreeBuilder(const std::vector<Token>& tokens, std::shared_ptr<VariableHandler> handler);

    StatementContainer& getTree() { return _root; }

private:
    std::shared_ptr<VariableHandler> _var_handler;
    StatementContainer _root;
    std::queue<std::vector<Token>> _statementTokens; // Tokens separated by statement termination

    /**
     * Separates tokens by statement termination
     */
    void getStatementTokens(const std::vector<Token>& tokens);

    /**
     * Identifies token
     */
    std::unique_ptr<Expr> identifyStatement(const std::vector<Token>& statement);

    bool statementMatchesRuleset(const std::vector<Token>& statement, std::span<const Token> ruleset);

private:
    inline static const std::array<Token, 2> _varInitializationRuleset = { { { Token::SubTypes::KEYWORD, "var" },
        { Token::MainTypes::VALUE, Token::SubTypes::IDENTIFIER } } };

    inline static const std::array<Token, 3> _varAssignmentRuleset = { { { Token::SubTypes::IDENTIFIER },
        { Token::SubTypes::ASSIGN }, { Token::MainTypes::VALUE, Token::SubTypes::ANY } } };

    inline static const std::array<Token, 4> _varInitializationAndAssignmentRuleset = { { { Token::SubTypes::KEYWORD },
        { Token::SubTypes::IDENTIFIER }, { Token::SubTypes::ASSIGN }, { Token::MainTypes::VALUE, Token::SubTypes::ANY } } };
};
