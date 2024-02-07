#include "gtest/gtest.h"
#include  "../include/long_arithmetic.h"

namespace {
    TEST(test_1, sum_of_bigF) {
        EXPECT_EQ(123.145_bigF, 100.0_bigF + 23.14_bigF + 0.005_bigF);
    }
    TEST(test_1, largesums){
        EXPECT_EQ(12478127519827.1289745_bigF-12465751644354.1289745_bigF, 12375875473.0_bigF);
    }

    TEST(test_2, edge_case) {
        EXPECT_EQ(10000.000000_bigF, 9999.999999_bigF + 0.000001_bigF);
    }

    TEST(test_3, substracting_test) {
        EXPECT_EQ(1000.0_bigF - 0.000001_bigF, 999.999999_bigF);
    }
    TEST(test_4, multiplying) {
        EXPECT_TRUE(13566.12_bigF * 351.651_bigF == 4770539.66412_bigF);
    }
    TEST(test_4, zero_multiplying) {
        EXPECT_EQ(0.004182_bigF * 0.004182_bigF, 0.000017489124_bigF);
    }

    TEST(test_5, basic_division) {
        EXPECT_EQ(1.0_bigF, 1.0_bigF / 1.0_bigF);
    }

    TEST(test_6, division_periodical) {
        EXPECT_EQ(2.0_bigF / 3.0_bigF,
                  0.666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666_bigF);
    }

    TEST(test_7, bigFloat_comparing) {
        EXPECT_TRUE(1.1111111_bigF > 1.111110_bigF);
    }

    TEST (test_8, equal_zeros) {
        EXPECT_EQ(-0.00_bigF, 0.00000000_bigF);
    }

    TEST (test_9, different_signs_compare) {
        EXPECT_GE(10.1240_bigF,
                  -1249815972591623857612379325.5178926913491236523864172365871234621834613875621034_bigF);
    }

    TEST (test_10, negative_substraction) {
        EXPECT_GT(1.01_bigF - (-1.041972_bigF), 2.05_bigF);
    }
    TEST (test_11, negative_sum) {
        EXPECT_LT(132458.123400_bigF + (-985478.56341254_bigF),-853020.450_bigF);
    }
    TEST (test_12, advanced_division) {
        EXPECT_EQ(1283592.12352734_bigF / 357571.58383_bigF, 3.589748686902361001855788882584931888881411843704672050869104432660252313428359266050685602658561795704536480364645535317453360622658066995200243286625486880764923338343454516560206495086687604809046830794971563610449441680959762970882942714626060054834866881709278581517756620330374534057392185811265_bigF);
    }
    //TODO: write more tests
    TEST (test_13, pi_calc) {
        LongNum pi = pie(100);
        EXPECT_EQ(pi, 3.0_bigF);
    }
}
