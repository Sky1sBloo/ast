#pragma once

#include "FunctionContainer.hpp"
#include "ParseNodes.hpp"
#include "Token.hpp"
#include "VariableHandler.hpp"
#include <memory>
#include <queue>
#include <vector>


/**
 * Class for parsing token vector
 */
class Parser {
public:
    Parser(const std::vector<Token>& tokens, std::shared_ptr<VariableHandler> handler, std::shared_ptr<FunctionContainer> container);

private:
    std::shared_ptr<VariableHandler> _variableHandler;
    std::shared_ptr<FunctionContainer> _functionContainer;
    std::queue<std::vector<Token>> _statementTokens;

    StatementContainer _root;
};
