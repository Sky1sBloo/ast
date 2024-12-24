#pragma once
#include "ParseNodes.hpp"
#include "Token.hpp"
#include "VariableHandler.hpp"

#include <array>
#include <memory>
#include <queue>
#include <optional>

class ParseTreeBuilder {
public:
    ParseTreeBuilder(const std::vector<Token>& tokens, std::shared_ptr<VariableHandler> handler, std::shared_ptr<FunctionContainer> funcContainer);

    StatementContainer& getTree() { return _root; }

private:
    std::shared_ptr<VariableHandler> _var_handler;
    std::shared_ptr<FunctionContainer> _func_container;
    StatementContainer _root;
    std::queue<std::vector<Token>> _statementTokens; // Tokens separated by statement termination

    /**
     * Separates tokens by statement termination
     */
    void getStatementTokens(const std::vector<Token>& tokens);

    /**
     * Identifies token
     *
     * @returns an unique expr if its not a function definition
     */
    std::optional<std::unique_ptr<Expr>> identifyStatement(const std::vector<Token>& statement);

    bool statementMatchesRuleset(const std::vector<Token>& statement, std::span<const Token> ruleset);

private:
    inline static const std::array<Token, 2> _varInitializationRuleset = { { { Token::SubTypes::KEYWORD, "var" },
        { Token::MainTypes::VALUE, Token::SubTypes::IDENTIFIER } } };

    inline static const std::array<Token, 3> _varAssignmentRuleset = { { { Token::SubTypes::IDENTIFIER },
        { Token::SubTypes::ASSIGN }, { Token::MainTypes::VALUE, Token::SubTypes::ANY } } };

    inline static const std::array<Token, 4> _varInitializationAndAssignmentRuleset = { { { Token::SubTypes::KEYWORD },
        { Token::SubTypes::IDENTIFIER }, { Token::SubTypes::ASSIGN }, { Token::MainTypes::VALUE, Token::SubTypes::ANY } } };

    inline static const std::array<Token, 4> _functionDefinitionRuleset = { { { Token::SubTypes::KEYWORD, "func" },
        { Token::SubTypes::IDENTIFIER }, { Token::SubTypes::OPERATOR, "(" }, { Token::SubTypes::OPERATOR, ")" } } };
};
