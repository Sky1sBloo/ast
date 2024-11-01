add_library(ast-lib ProgramMemory.cpp LiteralExpr.cpp InitializationExpr.cpp AssignExpr.cpp)
target_include_directories(ast-lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

