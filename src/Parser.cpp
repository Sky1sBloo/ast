#include "Parser.hpp"
#include "BaseParseNodes.hpp"
#include "FunctionDefinition.hpp"
#include <stdexcept>

Parser::Parser(const std::vector<Token>& tokens, std::shared_ptr<VariableHandler> handler, std::shared_ptr<FunctionContainer> container)
    : _variableHandler(handler)
    , _functionContainer(container)
    , _statementTokens()
    , _rulesetHandler(handler)
    , _currentFunction()
    , _root()
{
    retrieveStatements(tokens);
    buildTree();
}

void Parser::buildTree()
{
    while (!_statementTokens.empty()) {
        try {
            const std::vector<Token>& statement = _statementTokens.front();
            if (statement.empty()) {
                throw std::runtime_error("Empty statement on parser");
            }
            RulesetExpr rulesetExpr = _rulesetHandler.getExpression(statement);
            rulesetExpr.visit(
                [this](std::unique_ptr<Expr>& expr) {
                    if (_currentFunction.empty()) {
                        _root.insertExpr(std::move(expr));
                    } else {
                        _currentFunction.top()->insertExpr(std::move(expr));
                    }
                },
                [this](std::unique_ptr<FunctionDefinition>& function) {
                    _currentFunction.push(std::move(function));
                },
                [this]() {
                    if (_currentFunction.empty()) {
                        throw std::runtime_error("Tried to close unopened function");
                    }
                    _functionContainer->insertFunction(std::move(_currentFunction.top()));
                    _currentFunction.pop();
                },
                []() {
                    throw std::runtime_error("Invalid ruleset type");
                });
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
            }
            if (token.getValue() == "}") {
                if (!currentStatement.empty()) {
                    _statementTokens.push(currentStatement);
                    currentStatement.clear();
                }
                currentStatement.push_back(token);
                _statementTokens.push(currentStatement);
                currentStatement.clear();
                continue;
            }
        }
        currentStatement.push_back(token);
    }
}
