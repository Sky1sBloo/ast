add_executable(
    ast-unit-tests
    ProgramMemoryTests.cpp
    ParseNodesTests.cpp
)

target_link_libraries(
    ast-unit-tests
    PRIVATE
    ast-lib
    GTest::gtest_main
)

include (GoogleTest)
gtest_discover_tests(ast-unit-tests)
