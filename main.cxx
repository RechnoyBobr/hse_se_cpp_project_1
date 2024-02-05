#include <iostream>
#include <gtest/gtest.h>
#include "long_arithmetic.h"

int main() {
    testing::InitGoogleTest();
    const int res = RUN_ALL_TESTS();
    std::cout << (13566.12_bigF * 351.651_bigF == 4770539.66412_bigF) << "\n";
    const LongNum f = 0.0005_bigF+123.145_bigF;
    const LongNum f1 = f + 10000.0_bigF;
    std::cout << f1;
    return 0;
}
