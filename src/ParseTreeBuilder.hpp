#pragma once
#include "ParseNodes.hpp"
#include "Tokenizer.hpp"
#include "VariableHandler.hpp"

#include <memory>
#include <queue>

class ParseTreeBuilder {
    ParseTreeBuilder(const std::vector<Token>& tokens, std::shared_ptr<VariableHandler> handler);

private:
    std::unique_ptr<StatementContainer> _container;
    std::shared_ptr<VariableHandler> _handler;

    using StatementToken = std::unique_ptr<std::vector<Token>>;

    /**
     * Returns a queue of statements separated by termination statement
     */
    std::queue<StatementToken> getStatements(const std::vector<Token>& tokens);
};
