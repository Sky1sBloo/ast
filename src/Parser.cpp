#include "Parser.hpp"

Parser::Parser(const std::vector<Token>& tokens, std::shared_ptr<VariableHandler> handler, std::shared_ptr<FunctionContainer> container)
    : _variableHandler(handler), _functionContainer(container), _statementTokens(), _root()
{
}
