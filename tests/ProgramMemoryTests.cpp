#include <gtest/gtest.h>
#include <stdexcept>

#include "ProgramMemory.hpp"

TEST(PROGRAM_MEMORY_TEST, ALLOCATION_AND_ACCESS)
{
    ProgramMemory programMemory;
    std::string testValue = "123";

    int addr = programMemory.allocate(testValue);

    EXPECT_NO_THROW({
        std::string value = programMemory.retrieve(addr);
        ASSERT_EQ(value, testValue);
    });
}

TEST(PROGRAM_MEMORY_TEST, INVALID_ACCESS)
{
    ProgramMemory programMemory;
    EXPECT_THROW(std::string value = programMemory.retrieve(20), std::out_of_range);
}
