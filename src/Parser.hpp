#pragma once

#include "FunctionContainer.hpp"
#include "ParseNodes.hpp"
#include "ParserRulesets/RulesetHandler.hpp"
#include "Token.hpp"
#include "VariableHandler.hpp"
#include <memory>
#include <queue>
#include <stack>
#include <vector>

/**
 * Class for parsing token vector
 */
class Parser {
public:
    Parser(const std::vector<Token>& tokens, std::shared_ptr<VariableHandler> handler, std::shared_ptr<FunctionContainer> container);

    StatementContainer& getTree() { return _root; }

private:
    std::shared_ptr<VariableHandler> _variableHandler;
    std::shared_ptr<FunctionContainer> _functionContainer;
    std::queue<std::vector<Token>> _statementTokens;

    RulesetHandler _rulesetHandler;

    // Function to append new expression
    std::stack<std::unique_ptr<FunctionDefinition>> _currentFunction;
    StatementContainer _root;

private:
    /**
     * Separates tokens by delimiters
     */
    void retrieveStatements(const std::vector<Token>& tokens);

    /**
     * Builds the parse tree
     */
    void buildTree();
};
