#include "ParseTreeBuilder.hpp"
#include <queue>
#include <stack>
#include <stdexcept>
#include <vector>

ParseTreeBuilder::ParseTreeBuilder(const std::vector<Token>& tokens, std::shared_ptr<VariableHandler> handler)
    : _container(std::make_unique<StatementContainer>())
    , _handler(handler)
{
    std::queue<StatementToken> statements = getStatements(tokens);

    // Iterate each statement
    while (!statements.empty()) {
        auto& statement = statements.front();
        std::stack<Token> valueTokens;

        for (const Token& token : *statement) {
            if (token.isValue()) {
                valueTokens.push(token);
            } else {
                if (token.type == Token::Types::ASSIGN) {
                    auto assignExpr = getAssignmentExpr(valueTokens);
                    _container->insertExpr(std::move(assignExpr));
                }
            }
        }
    }
}

std::queue<ParseTreeBuilder::StatementToken> ParseTreeBuilder::getStatements(const std::vector<Token>& tokens)
{
    std::queue<StatementToken> statements;
    std::vector<Token> statement;

    for (const Token& token : tokens) {
        if (token.type == Token::Types::STATEMENT_TERMINATE) {
            StatementToken postFixStatement = getPostFix(statement);
            statements.push(std::move(postFixStatement));
            continue;
        }
        statement.push_back(token);
    }

    return statements;
}

ParseTreeBuilder::StatementToken ParseTreeBuilder::getPostFix(const std::vector<Token>& statement)
{
    StatementToken postFixToken;
    std::stack<Token> terminalTokens;
    for (const Token& token : statement) {
        if (token.isTerminal()) {
            if (terminalTokens.empty() || token.getTerminalPrecedence() > terminalTokens.top().getTerminalPrecedence()) {
                terminalTokens.push(token);
            } else {
                while (terminalTokens.top().getTerminalPrecedence() >= token.getTerminalPrecedence()) {
                    postFixToken->push_back(token);
                    terminalTokens.pop();
                }
                terminalTokens.push(token);
            }
        } else {
            postFixToken->push_back(token);
        }
    }

    return postFixToken;
}

std::unique_ptr<AssignExpr> ParseTreeBuilder::getAssignmentExpr(std::stack<Token>& valueTokens)
{
    if (valueTokens.size() < 2) {
        throw std::invalid_argument("Assignment Expression missing arguments");
    }
    const Token& value = valueTokens.top();
    valueTokens.pop();
    const Token& identifier = valueTokens.top();
    valueTokens.pop();

    if (identifier.type != Token::Types::IDENTIFIER) {
        throw std::invalid_argument("Assignment Expression identifier not token");
    }

    return std::make_unique<AssignExpr>(identifier.value, std::make_unique<LiteralExpr>(value.value), _handler);
}
