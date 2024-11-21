#pragma once
#include "ParseNodes.hpp"
#include "Token.hpp"
#include "VariableHandler.hpp"

#include <memory>
#include <queue>
#include <stack>

template <class... TokenVariant>
struct TokenVisitor : TokenVariant... {
    using TokenVariant::operator()...;
};
class ParseTreeBuilder {
public:
    ParseTreeBuilder(const std::vector<Token>& tokens, std::shared_ptr<VariableHandler> handler);

    std::unique_ptr<StatementContainer> getTree() {
        return std::move(_container);
    } 
private:
    std::shared_ptr<VariableHandler> _handler;
    std::unique_ptr<StatementContainer> _container;

    using StatementToken = std::unique_ptr<std::vector<Token>>;

    /**
     * Returns a queue of statements separated by termination statement
     */
    StatementToken getPostFix(const std::vector<Token>& statement);
    std::queue<StatementToken> getStatements(const std::vector<Token>& tokens);

    /**
     * Constructs a assign expr from valueStack
     *
     * @param valueStack contains value and identifier
     * Modifies valueStack
     */
    std::unique_ptr<AssignExpr> getAssignmentExpr(std::stack<Token>& valueStack);

    /**
     * Constructs a initialization expr from valueStack
     *
     * @param valueStack contains value and identifier
     * Modifies valueStack
     */
    std::unique_ptr<InitializationExpr> getInitializationExpr(std::stack<Token>& valueStack);
};
