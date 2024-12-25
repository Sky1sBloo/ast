/**
 * This header contains all ruleset functions
 */
#pragma once

#include "BaseParseNodes.hpp"
#include "Token.hpp"
#include "VariableHandler.hpp"
#include <initializer_list>
#include <memory>
#include <vector>

/**
 * Base class for a ruleset
 */
class ParserRuleset {
public:
    ParserRuleset(std::shared_ptr<VariableHandler> handler)
        : _handler(handler)
    {
    }

    /**
     * Creates and determines if the statement is a valid rule
     *
     * @param statement Statement to be checked
     * @return nullptr if invalid
     */
    virtual std::unique_ptr<Expr> createExpr(const std::vector<Token>& statement) = 0;

    /**
     * Function for handling exact match ruleset
     */
    static bool statementMatchesRuleset(const std::vector<Token>& statement, const std::vector<Token>& ruleset);

protected:
    std::shared_ptr<VariableHandler> _handler;
};

/**
 * Class for handling the variable initialization ruleset
 */
class VariableInitializationRuleset : public ParserRuleset {
public:
    VariableInitializationRuleset(std::shared_ptr<VariableHandler> handler);

    std::unique_ptr<Expr> createExpr(const std::vector<Token>& statement) override;

private:
    inline static const std::vector<Token> _ruleset = { { { Token::SubTypes::KEYWORD, "var" },
        { Token::SubTypes::IDENTIFIER },
        { Token::SubTypes::STATEMENT_TERMINATE } } };
};

/**
 * Class for handling assignment ruleset
 */
class VariableAssignmentRuleset : public ParserRuleset {
public:
    VariableAssignmentRuleset(std::shared_ptr<VariableHandler> handler);
    std::unique_ptr<Expr> createExpr(const std::vector<Token>& statement) override;

private:
    inline static const std::vector<Token> _ruleset = { { { Token::SubTypes::IDENTIFIER },
        { Token::SubTypes::ASSIGN }, { Token::MainTypes::VALUE, Token::SubTypes::ANY }, { Token::SubTypes::STATEMENT_TERMINATE } } };
};

class VariableInitializatonAndAssignmentRuleset : public ParserRuleset {
public:
    VariableInitializatonAndAssignmentRuleset(std::shared_ptr<VariableHandler> handler);
    std::unique_ptr<Expr> createExpr(const std::vector<Token>& statement) override;

private:
    inline static const std::vector<Token> _ruleset = { { { Token::SubTypes::KEYWORD },
        { Token::SubTypes::IDENTIFIER }, { Token::SubTypes::ASSIGN }, { Token::MainTypes::VALUE, Token::SubTypes::ANY },
        { Token::SubTypes::STATEMENT_TERMINATE } } };
};
