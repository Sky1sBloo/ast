#include "MemoryCell.hpp"
#include <gtest/gtest.h>

TEST(MEMORY_CELL_TESTS, FLOAT_TEST)
{
    std::string value = "5.03";
    float expectedValue = 5.03f;

    MemoryCell cell(value);

    EXPECT_NO_THROW({
        if (!cell.getAs<float>().has_value()) {
            FAIL();
        }
        float cellValue = cell.getAs<float>().value();
        EXPECT_FLOAT_EQ(expectedValue, cellValue);
    });

    EXPECT_EQ(DataType::FLOAT, cell.getType());
}

TEST(MEMORY_CELL_TESTS, INT_TEST)
{
    std::string value = "53";
    int expectedValue = 53;

    MemoryCell cell(value);

    EXPECT_EQ(DataType::INT, cell.getType());
    EXPECT_NO_THROW({
        if (!cell.getAs<int>().has_value()) {
            FAIL();
        }
        int cellValue = cell.getAs<int>().value();
        EXPECT_EQ(expectedValue, cellValue);
    });
}
