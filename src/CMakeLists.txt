add_library(ast-lib ProgramMemory.cpp VariableHandler.cpp ParseNodes/LiteralExpr.cpp ParseNodes/InitializationExpr.cpp ParseNodes/AssignExpr.cpp)
target_include_directories(ast-lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/ParseNodes)

