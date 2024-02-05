#include "gtest/gtest.h"
#include  "long_arithmetic.h"

namespace {
    TEST(test_1, sum_of_bigF) {
        EXPECT_EQ(123.145_bigF, 100.0_bigF+23.14_bigF+0.005_bigF);
    }

    TEST(test_2, edge_case) {
        EXPECT_EQ((10000.000000_bigF).toStr(), (9999.999999_bigF+0.000001_bigF).toStr());
    }

    TEST(test_3, substracting_test) {
        EXPECT_EQ((1000.0_bigF-0.000001_bigF).toStr(), (999.999999_bigF).toStr());
    }

    TEST(test_4, multiplying) {
        EXPECT_TRUE(13566.12_bigF * 351.651_bigF == 4770539.66412_bigF);
    }

    TEST(test_5, basic_division) {
        EXPECT_EQ(1.0_bigF, 1.0_bigF / 1.0_bigF);
    }
}
