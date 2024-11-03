#include <gtest/gtest.h>
#include <stdexcept>

#include "MemoryCell.hpp"
#include "ProgramMemory.hpp"

TEST(PROGRAM_MEMORY_TEST, ALLOCATION_AND_ACCESS)
{
    ProgramMemory programMemory;
    std::string testValue = "123";
    int expectedValue = 123;

    int addr = programMemory.allocate(testValue);

    EXPECT_NO_THROW({
        const MemoryCell& value = programMemory.retrieve(addr);
        if (!value.getAs<int>().has_value()) {
            FAIL();
        }
        int cellValue = value.getAs<int>().value();
        ASSERT_EQ(cellValue, expectedValue);
    });
}

TEST(PROGRAM_MEMORY_TEST, INVALID_ACCESS)
{
    ProgramMemory programMemory;
    EXPECT_THROW(const MemoryCell& value = programMemory.retrieve(20), std::out_of_range);
}

TEST(PROGRAM_MEMORY_TEST, SET)
{
    ProgramMemory programMemory;
    std::string testValue = "123";
    std::string updatedValue = "234";
    int expectedValue = 234;

    int addr = programMemory.allocate(testValue);
    EXPECT_NO_THROW({
        programMemory.set(addr, updatedValue);
    });

    EXPECT_NO_THROW({
        const MemoryCell& value = programMemory.retrieve(addr);
        ASSERT_EQ(value.getAs<int>().value(), expectedValue);
    });
}
