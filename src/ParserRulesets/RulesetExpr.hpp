#pragma once
#include "BaseParseNodes.hpp"
#include "FunctionDefinition.hpp"
#include <functional>
#include <variant>

/**
 * Class container for ruleset returns
 */
class RulesetExpr {
public:
    enum class Types {
        INVALID,  // It means that the ruleset is not valid for that specific ruleset
        EXPR,
        FUNCTION_DEFINITION,
        FUNCTION_TERMINATION
    };

    // Constructor for expression
    RulesetExpr(std::unique_ptr<Expr> expr);

    // Constructor for function definition
    RulesetExpr(std::unique_ptr<FunctionDefinition> functionDefinition);

    // Constructor for function termination only
    RulesetExpr(Types type);

    // Constructor for empty ruleset
    RulesetExpr();

    /**
     * Retrieves the type of ruleset
     */
    Types getTypes() const { return _type; }

    /**
     * Retrieves the expression based on _type
     */
    void visit(std::function<void(std::unique_ptr<Expr>&)> exprVisitor,
        std::function<void(std::unique_ptr<FunctionDefinition>&)> functionVisitor,
        std::function<void()> terminationVisitor, std::function<void()> noneVisitor);;

private:
    using RulesetVariant = std::variant<std::monostate, std::unique_ptr<Expr>, std::unique_ptr<FunctionDefinition>>;

    RulesetVariant _variant;
    Types _type;
};
