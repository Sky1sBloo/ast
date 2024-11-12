#pragma once
#include "ParseNodes.hpp"
#include "Token.hpp"
#include "VariableHandler.hpp"

#include <memory>
#include <queue>
#include <stack>

class ParseTreeBuilder {
    ParseTreeBuilder(const std::vector<TokenContainer>& tokens, std::shared_ptr<VariableHandler> handler);

private:
    std::unique_ptr<StatementContainer> _container;
    std::shared_ptr<VariableHandler> _handler;

    using StatementToken = std::unique_ptr<std::vector<TokenContainer>>;

    /**
     * Returns a queue of statements separated by termination statement
     */
    template<class... TokenVariant>
    struct TokenVisitor : TokenVariant... { using TokenVariant::operator()...; };
    StatementToken getPostFix(const std::vector<TokenContainer>& statement);
    std::queue<StatementToken> getStatements(const std::vector<TokenContainer>& tokens);

    /**
     * Constructs a assign expr from valueStack
     *
     * @param valueStack contains value and identifier
     * Modifies valueStack
    */
    std::unique_ptr<AssignExpr> getAssignmentExpr(std::stack<ValueToken>& valueStack);
};
