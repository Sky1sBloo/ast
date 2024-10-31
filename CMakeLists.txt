cmake_minimum_required(VERSION 3.30)

project (ast LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(src)
add_executable(ast main.cpp)
target_link_libraries(ast PRIVATE ast-lib)
