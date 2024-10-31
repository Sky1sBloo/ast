#include <gtest/gtest.h>

#include "ProgramMemory.hpp"

TEST(PROGRAM_MEMORY_TEST, ALLOCATION_AND_ACCESS)
{
    ProgramMemory programMemory;
    std::string testValue = "123";

    int addr = programMemory.allocate(testValue);
    std::string value = programMemory.retrieve(addr);

    ASSERT_EQ(value, testValue);
}

TEST(PROGRAM_MEMORY_TEST, INVALID_ACCESS)
{
    ProgramMemory programMemory;
    std::string value = programMemory.retrieve(20);

    ASSERT_EQ(value, "INVALID_ACCESS");
}
