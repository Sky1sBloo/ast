add_library(ast-lib 
    Tokenizer.cpp 
    ProgramMemory.cpp 
    MemoryCell.cpp 
    VariableHandler.cpp 
    ParseTreeBuilder.cpp 
    FunctionContainer.cpp
    Parser.cpp
    ParserRulesets/ParserRuleset.cpp
    ParserRulesets/VariableInitializationRuleset.cpp
    ParseNodes/LiteralExpr.cpp 
    ParseNodes/InitializationExpr.cpp 
    ParseNodes/AssignExpr.cpp 
    ParseNodes/StatementContainer.cpp
    ParseNodes/FunctionDefinition.cpp
    ParseNodes/FunctionCallExpr.cpp)
target_include_directories(ast-lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/ParseNodes)

