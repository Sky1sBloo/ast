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
    , _currentFunction()
    , _root()
{
    retrieveStatements(tokens);

    while (!_statementTokens.empty()) {
        try {
            RulesetExpr rulesetExpr = _rulesetHandler.getExpression(_statementTokens.front());
            if (std::holds_alternative<std::unique_ptr<Expr>>(rulesetExpr)) {
                // To insert on function when its defined
                if (_currentFunction.empty()) {
                    _root.insertExpr(std::move(std::get<std::unique_ptr<Expr>>(rulesetExpr)));
                } else {
                    _currentFunction.top()->insertExpr(std::move(std::get<std::unique_ptr<Expr>>(rulesetExpr)));
                }
            } else if (std::holds_alternative<std::unique_ptr<FunctionDefinition>>(rulesetExpr)) {
                _currentFunction.push(std::move(std::get<std::unique_ptr<FunctionDefinition>>(rulesetExpr)));
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
                continue;
            } else if (token.getValue() == "}") {
                if (_currentFunction.empty()) {
                    // Todo: Log this error
                    throw std::invalid_argument("Tried to close brace on unopened function");
                }
                _functionContainer->insertFunction(std::move(_currentFunction.top()));
                _currentFunction.pop();
                continue;
            }
        }
        currentStatement.push_back(token);
    }
}
