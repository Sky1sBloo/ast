add_library(ast-lib 
    Tokenizer.cpp 
    ProgramMemory.cpp 
    MemoryCell.cpp 
    VariableHandler.cpp 
    FunctionContainer.cpp
    Parser.cpp
    ParserRulesets/RulesetExpr.cpp
    ParserRulesets/RulesetHandler.cpp
    ParserRulesets/ParserRuleset.cpp
    ParserRulesets/VariableAssignmentRuleset.cpp
    ParserRulesets/VariableInitializationRuleset.cpp
    ParserRulesets/VariableInitializationAndAssignmentRuleset.cpp
    ParserRulesets/FunctionDefinitionRuleset.cpp
    ParserRulesets/FunctionReturnRuleset.cpp
    ParserRulesets/FunctionTerminationRuleset.cpp
    ParseNodes/Expr.cpp
    ParseNodes/LiteralExpr.cpp 
    ParseNodes/InitializationExpr.cpp 
    ParseNodes/AssignExpr.cpp 
    ParseNodes/StatementContainer.cpp
    ParseNodes/FunctionDefinition.cpp
    ParseNodes/FunctionCallExpr.cpp)
target_include_directories(ast-lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/ParseNodes)

