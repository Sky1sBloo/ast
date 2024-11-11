#include "ParseTreeBuilder.hpp"
#include "ParseNodes.hpp"
#include <queue>
#include <stack>
#include <vector>

ParseTreeBuilder::ParseTreeBuilder(const std::vector<Token>& tokens, std::shared_ptr<VariableHandler> handler)
    : _container(std::make_unique<StatementContainer>())
    , _handler(handler)
{
    std::queue<StatementToken> statements = getStatements(tokens);

    // Iterate each statement
    while (!statements.empty()) {
        auto& statement = statements.front();
        std::queue<Token> valueTokens;

        for (Token token : *statement) {
            if (token.isValue()) {
                valueTokens.push(token);
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
