#include <iostream>
#include <gtest/gtest.h>
#include "long_arithmetic.h"

int main() {
    testing::InitGoogleTest();
    const int res = RUN_ALL_TESTS();
    const LongNum f = 0.0005_bigF+123.145_bigF;
    const LongNum f1 = f + 10000.0_bigF;
    return 0;
}
