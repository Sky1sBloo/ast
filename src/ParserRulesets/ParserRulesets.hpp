/**
 * This header contains all ruleset functions
 */
#pragma once

#include "BaseParseNodes.hpp"
#include "FunctionDefinition.hpp"
#include "Token.hpp"
#include "VariableHandler.hpp"
#include <initializer_list>
#include <memory>
#include <variant>
#include <vector>

using RulesetExpr = std::variant<std::monostate, std::unique_ptr<Expr>, std::unique_ptr<FunctionDefinition>>;

/**
 * Base class for a ruleset
 */
class ParserRuleset {
public:
    ParserRuleset(std::shared_ptr<VariableHandler> handler)
        : _handler(handler)
    {
    }

    virtual ~ParserRuleset() { }

    /**
     * Creates and determines if the statement is a valid rule
     *
     * @param statement Statement to be checked
     * @return nullptr if invalid
     */
    virtual RulesetExpr createExpr(const std::vector<Token>& statement) const = 0;

protected:
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

    RulesetExpr createExpr(const std::vector<Token>& statement) const override;

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
    RulesetExpr createExpr(const std::vector<Token>& statement) const override;

private:
    inline static const std::vector<Token> _ruleset = { { { Token::SubTypes::IDENTIFIER },
        { Token::SubTypes::ASSIGN }, { Token::MainTypes::VALUE, Token::SubTypes::ANY }, { Token::SubTypes::STATEMENT_TERMINATE } } };
};

/**
 * Class for handling initialization and assignment ruleset
 */
class VariableInitializationAndAssignmentRuleset : public ParserRuleset {
public:
    VariableInitializationAndAssignmentRuleset(std::shared_ptr<VariableHandler> handler);
    RulesetExpr createExpr(const std::vector<Token>& statement) const override;

private:
    inline static const std::vector<Token> _ruleset = { { { Token::SubTypes::KEYWORD },
        { Token::SubTypes::IDENTIFIER }, { Token::SubTypes::ASSIGN }, { Token::MainTypes::VALUE, Token::SubTypes::ANY },
        { Token::SubTypes::STATEMENT_TERMINATE } } };
};
