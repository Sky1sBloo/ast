#include "ParseTreeBuilder.hpp"
#include "ParseNodes.hpp"
#include <queue>
#include <vector>

ParseTreeBuilder::ParseTreeBuilder(const std::vector<Token>& tokens, std::shared_ptr<VariableHandler> handler)
    : _container(std::make_unique<StatementContainer>())
    , _handler(handler)
{
    std::queue<StatementToken> statements = getStatements(tokens);

    // Iterate each statement
    while (!statements.empty()) {
        auto& statement = statements.front();
        for (int i = 0; i < statement->size(); i++) {
            const Token& token = statement->at(i);

            if (token.type == Token::Types::ASSIGN) {
                if (i == 0) {
                    throw;
                }

                const Token& identifier = statement->at(i - 1);
                if (identifier.type != Token::Types::IDENTIFIER) {
                    throw;
                }

                const Token& value = statement->at(i + 1);
                if (!value.isValue()) {
                    throw;
                }

                auto literalExpr = std::make_unique<LiteralExpr>(value.value);
                _container->insertExpr(std::make_unique<AssignExpr>(identifier.value, std::move(literalExpr), _handler));
                continue;
            }
        }
        statements.pop();
    }
}

std::queue<std::unique_ptr<std::vector<Token>>> ParseTreeBuilder::getStatements(const std::vector<Token>& tokens)
{
    std::queue<StatementToken> statements;
    StatementToken statement;

    // TODO READ UNTIL STATEMENT_END
    for (const Token& token : tokens) {
        if (token.type == Token::Types::STATEMENT_TERMINATE) {
            statements.push(std::move(statement));
            continue;
        }
        statement->push_back(token);
    }

    return statements;
}
