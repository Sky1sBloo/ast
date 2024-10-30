cmake_minimum_required(VERSION 3.30)
project (ast)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD ON)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 18.1.2)
        message(FATAL_ERROR "Clang version must be atleast 18.1.2")
    endif()
else()
    message(FATAL_ERROR "Project requires Clang 18.1.2 or above")
endif()

add_executable(ast main.cpp)
