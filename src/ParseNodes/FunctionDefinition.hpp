#pragma once

#include "BaseParseNodes.hpp"
#include <string>
#include <memory>
#include <vector>

/**
 * Node for returnable functions
 */
class FunctionDefinition {
public:
    FunctionDefinition(const std::string& id);
    FunctionDefinition(const std::string& id, const std::vector<std::string>& params);
    ~FunctionDefinition();
    void insertExpr(std::unique_ptr<Expr> expr);
    void insertExpr(std::unique_ptr<ReturnableExpr> expr);
    void insertExpr(std::unique_ptr<TerminalExpr> expr);

    const MemoryCell& getValue();
    const MemoryCell& getValue(const std::vector<MemoryCell&>& params);
    const std::string& getId() const
    {
        return _id;
    }

    const std::vector<std::string>& getParams() const {
        return _params;
    }

private:
    const std::string _id;
    std::vector<std::unique_ptr<Expr>> _statements;
    std::vector<std::string> _params;
};
