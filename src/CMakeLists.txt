add_library(ast-lib BinaryConditionExpr.cpp ProgramMemory.cpp VariableExpr.cpp)
target_include_directories(ast-lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

