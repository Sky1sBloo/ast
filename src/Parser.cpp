#include "Parser.hpp"
#include "FunctionDefinition.hpp"
#include "ParserRulesets/ParserRulesets.hpp"
#include <stdexcept>
#include <variant>

Parser::Parser(const std::vector<Token>& tokens, std::shared_ptr<VariableHandler> handler, std::shared_ptr<FunctionContainer> container)
    : _variableHandler(handler)
    , _functionContainer(container)
    , _statementTokens()
    , _rulesetHandler(handler)
    , _root()
{
    retrieveStatements(tokens);

    while (!_statementTokens.empty()) {
        try {
            RulesetExpr rulesetExpr = _rulesetHandler.getExpression(_statementTokens.front());
            if (std::holds_alternative<std::unique_ptr<Expr>>(rulesetExpr)) {
                _root.insertExpr(std::move(std::get<std::unique_ptr<Expr>>(rulesetExpr)));
            } else if (std::holds_alternative<std::unique_ptr<FunctionDefinition>>(rulesetExpr)) {
                _functionContainer->insertFunction(std::move(std::get<std::unique_ptr<FunctionDefinition>>(rulesetExpr)));
            }
        } catch (std::invalid_argument ex) {
            // TODO: Log this error
            throw ex;
        }
        _statementTokens.pop();
    }
}

void Parser::retrieveStatements(const std::vector<Token>& tokens)
{
    std::vector<Token> currentStatement;
    for (const Token& token : tokens) {

        if (token.getSubType() == Token::SubTypes::STATEMENT_TERMINATE) {
            // TODO: Handle opening and closing braces
            currentStatement.push_back(token);
            _statementTokens.push(currentStatement);
            currentStatement.clear();
            continue;
        }

        if (token.getSubType() == Token::SubTypes::BRACE) {
            if (token.getValue() == "{") {
                currentStatement.push_back(token);
                _statementTokens.push(currentStatement);
                currentStatement.clear();
            }
        }
        currentStatement.push_back(token);
    }
}
