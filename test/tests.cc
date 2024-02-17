#include "gtest/gtest.h"
#include  "../include/long_arithmetic.h"
#include <iostream>

namespace {
    TEST(test_1, sum_of_bigF) {
        EXPECT_EQ(123.145_bigF, 100.0_bigF + 23.14_bigF + 0.005_bigF);
    }

    TEST(test_1, largesums) {
        EXPECT_EQ(12478127519827.1289745_bigF - 12465751644354.1289745_bigF, 12375875473.0_bigF);
        EXPECT_EQ(500000000.0_bigF + 500000000.0_bigF, 1000000000.0_bigF);
        EXPECT_EQ(10.0000000001234_bigF + 12.123_bigF, 22.1230000001234_bigF);
        EXPECT_EQ(100.0_bigF + 0.0_bigF, 100.0_bigF);
    }

    TEST(test_2, edge_case) {
        EXPECT_EQ(10000.000000_bigF, 9999.999999_bigF + 0.000001_bigF);
    }

    TEST(test_3, substracting_test) {
        EXPECT_EQ(1000.0_bigF - 0.000001_bigF, 999.999999_bigF);
        EXPECT_EQ(124124.0748381749283130_bigF - 100.0_bigF, 124024.0748381749283130_bigF);
        EXPECT_EQ(100.0_bigF - 101.0_bigF, -1.0_bigF);
        EXPECT_EQ(-100.0_bigF - (-100.0_bigF), 0.0_bigF);
        EXPECT_EQ(1000000012.0_bigF - 1000000000.0_bigF, 12.0_bigF);
        EXPECT_FALSE(1.0412_bigF == 1.0412000002_bigF);
        EXPECT_FALSE(1.0412000002_bigF == 1.0412_bigF);
        EXPECT_GT(-1230.0123_bigF - (-123852983.0_bigF), 0.0_bigF);
        EXPECT_GT(123.0_bigF - (-123.0_bigF), 100.0_bigF);
        EXPECT_NE(120.0_bigF, 0.0_bigF);
        EXPECT_EQ(-10.0_bigF - (-5.0_bigF), -5.0_bigF);
        EXPECT_EQ(-100.0_bigF - 23.104_bigF, -123.104_bigF);
        EXPECT_FALSE(123.0123_bigF >= 12341.0_bigF);
    }

    TEST(test_4, multiplying) {
        EXPECT_TRUE(13566.12_bigF * 351.651_bigF == 4770539.66412_bigF);
        EXPECT_EQ(50000.0_bigF * 90000.0_bigF, 4500000000.0_bigF);
        EXPECT_EQ(0.004182_bigF * 0.004182_bigF, 0.000017489124_bigF);
        EXPECT_EQ(0.0_bigF * 12314.412040182_bigF, 0.0_bigF);
    }

    TEST(test_5, bigFloat_comparing) {
        EXPECT_TRUE(1.1111111_bigF > 1.111110_bigF);
        EXPECT_GE(123.001_bigF, -157375773.0_bigF);
        EXPECT_GE(-1230.0123_bigF, -12427.0241_bigF);
        EXPECT_FALSE(100.0_bigF > 200.0_bigF);
        EXPECT_FALSE(12.412354133457238479875298374_bigF < 12.412354133_bigF);
        EXPECT_EQ(1012314.1240512074_bigF, 1012314.1240512074000000_bigF);
        EXPECT_LT(123.00123_bigF, 123.001230000012_bigF);
        EXPECT_LT(123843928492134.0_bigF, 48282374983748912365897364879213648793648721362187365.0_bigF);
        EXPECT_LT(-123.0_bigF, 23.0_bigF);
    }

    TEST (test_6, equal_zeros) {
        EXPECT_EQ(-0.00_bigF, 0.00000000_bigF);
    }


    TEST (test_7, different_signs_compare) {
        EXPECT_GE(10.1240_bigF,
                  -1249815972591623857612379325.5178926913491236523864172365871234621834613875621034_bigF);
    }

    TEST(test_8, basic_division) {
        EXPECT_EQ(1.0_bigF, 1.0_bigF / 1.0_bigF);
        EXPECT_EQ(1.0_bigF / (-10.0_bigF), -0.1_bigF);
    }

    TEST(test_9, division_periodical) {
        EXPECT_EQ(2.0_bigF / 3.0_bigF,
                  0.666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666_bigF);
    }


    TEST (test_10, negative_substraction) {
        EXPECT_GT(1.01_bigF - (-1.041972_bigF), 2.05_bigF);
    }

    TEST (test_11_1, negative_sum) {
        EXPECT_EQ(132458.123400_bigF + (-985478.56341254_bigF), -853020.44001254_bigF);
    }

    TEST(test_11_2, negative_sum) {
        EXPECT_GT(-985478.56341254_bigF + 132458.123400_bigF, -853020.450_bigF);
    }

    TEST (test_12, advanced_division) {
        EXPECT_EQ(1283592.12352734_bigF / 357571.58383_bigF,
                  3.589748686902361001855788882584931888881411843704672050869104432660252313428359266050685602658561795704536480364645535317453360622658066995200243286625486880764923338343454516560206495086687604809046830794971563610449441680959762970882942714626060054834866881709278581517756620330374534057392185811265_bigF);
        long_num::LongNum n = (239.0_bigF).inverse_number(200);
        EXPECT_EQ(n, 0.004184100418410041841004184100418410041841004184100418410041841004184100418410041841004184100418410041841004184100418410041841004184100418410041841004184100418410041841004184100418410041841004184100418410041841004184100418410041841004184100418410041841004184100418410041841004184100418410041841004184_bigF);
    }

    TEST (test_14_1, toStr_test) {
        EXPECT_EQ((123.000123_bigF).toStr(), "123.000123");
    }

    TEST(test_14_2, toStr_test_padding) {
        EXPECT_EQ((-21412.123000_bigF).toStr(), "-21412.123");
    }

    TEST(test_15, division_with_zero) {
        EXPECT_EQ(0.0_bigF / 12453471232894712834.35472384172847612387462864123876487234_bigF, 0.0_bigF);
    }

    TEST(test_15, zero_division) {
        try {
            1.0_bigF / 0.0_bigF;
        }
        catch (const std::runtime_error &err) {
            EXPECT_EQ(*err.what(), *std::runtime_error("Error: division by 0").what());
        }
    }

    TEST(test_16, inverse) {
        EXPECT_EQ((1.0_bigF).inverse_number(200), 1.0_bigF);
    }

    TEST(test_17, equal_comp) {
        EXPECT_EQ(1.0_bigF != 1.00_bigF, false);
    }

    TEST(test_18, strip_test) {
        long_num::LongNum t = 3.12345678910_bigF;
        t.strip(9);
        EXPECT_EQ(t, 3.123456789_bigF);
    }

    TEST(test_19, sum_equal_test) {
        long_num::LongNum t1 = 10.0_bigF, t2 = 13.23_bigF;
        t1 += t2;
        EXPECT_EQ(t1, 23.23_bigF);
        t1 -= 2.0_bigF * t2;
        EXPECT_EQ(t1, -3.23_bigF);
    }

    TEST(test_20, cout_test) {
        long_num::LongNum t1 = 123040123.012481293_bigF;
        std::cout << t1;
        EXPECT_EQ(t1, 123040123.012481293_bigF);
    }
}
