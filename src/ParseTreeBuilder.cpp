#include "ParseTreeBuilder.hpp"
#include "Token.hpp"
#include <iostream>
#include <queue>
#include <stack>
#include <stdexcept>
#include <vector>

ParseTreeBuilder::ParseTreeBuilder(const std::vector<TokenContainer>& tokens, std::shared_ptr<VariableHandler> handler)
    : _container(std::make_unique<StatementContainer>())
    , _handler(handler)
{
    std::queue<StatementToken> statements = getStatements(tokens);

    // Iterate each statement
    while (!statements.empty()) {
        auto& statement = statements.front();
        std::stack<ValueToken> valueTokens;

        for (const TokenContainer& tokenContainer : *statement) {
            if (std::holds_alternative<ValueToken>(tokenContainer.getToken())) {
                valueTokens.push(std::get<ValueToken>(tokenContainer.getToken()));
            } else if (std::holds_alternative<TerminalToken>(tokenContainer.getToken())) {
                const TerminalToken& token = std::get<TerminalToken>(tokenContainer.getToken());
                if (token.type == Token::Types::ASSIGN) {
                    auto assignExpr = getAssignmentExpr(valueTokens);
                    _container->insertExpr(std::move(assignExpr));
                }
            }
        }
        statements.pop();
    }
}

std::queue<ParseTreeBuilder::StatementToken> ParseTreeBuilder::getStatements(const std::vector<TokenContainer>& tokens)
{
    // Todo make this more efficient
    std::queue<StatementToken> statements;
    std::vector<TokenContainer> statement;

    for (const TokenContainer& tokenContainer : tokens) {
        std::visit([&](const Token& token) {
            if (token.type == Token::Types::STATEMENT_TERMINATE) {
                StatementToken postFixStatement = getPostFix(statement);
                statements.push(std::move(postFixStatement));
                statement.clear();
            } else {
                statement.push_back(tokenContainer);
            }
        },
            tokenContainer.getToken());
    }

    return statements;
}

ParseTreeBuilder::StatementToken ParseTreeBuilder::getPostFix(const std::vector<TokenContainer>& statement)
{
    StatementToken postFixToken = std::make_unique<std::vector<TokenContainer>>();
    std::stack<TerminalToken> terminalTokens;

    for (const TokenContainer& tokenContainer : statement) {
        std::visit(TokenVisitor {
                       [&postFixToken](const ValueToken& valueToken) {
                           postFixToken->emplace_back(valueToken.type, valueToken.value);
                       },
                       [&postFixToken, &terminalTokens](const TerminalToken& terminalToken) {
                           while (!terminalTokens.empty() && terminalTokens.top().getPrecedence() >= terminalToken.getPrecedence()) {
                               postFixToken->emplace_back(terminalTokens.top().type, terminalTokens.top().value);
                               terminalTokens.pop();
                           }
                           terminalTokens.push(terminalToken);
                       } },
            tokenContainer.getToken());
    }

    while (!terminalTokens.empty()) {
        postFixToken->emplace_back(terminalTokens.top().type, terminalTokens.top().value);
        terminalTokens.pop();
    }

    return postFixToken;
}

std::unique_ptr<AssignExpr> ParseTreeBuilder::getAssignmentExpr(std::stack<ValueToken>& valueTokens)
{
    if (valueTokens.size() < 2) {
        throw std::invalid_argument("Assignment Expression missing arguments");
    }
    const ValueToken& value = valueTokens.top();
    valueTokens.pop();
    const ValueToken& identifier = valueTokens.top();
    valueTokens.pop();

    if (identifier.type != Token::Types::IDENTIFIER) {
        throw std::invalid_argument("Assignment Expression identifier not token");
    }

    return std::make_unique<AssignExpr>(identifier.value, std::make_unique<LiteralExpr>(value.value), _handler);
}
