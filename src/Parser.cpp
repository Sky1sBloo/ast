#include "Parser.hpp"
#include <stdexcept>

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
            std::unique_ptr<Expr> expr = _rulesetHandler.getExpression(_statementTokens.front());
            _root.insertExpr(std::move(expr));
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
        currentStatement.push_back(token);

        if (token.getSubType() == Token::SubTypes::STATEMENT_TERMINATE) {
            // TODO: Handle opening and closing braces
            _statementTokens.push(currentStatement);
            currentStatement.clear();
        }
    }
}
