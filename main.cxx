#include <iostream>
#include <gtest/gtest.h>
#include "long_arithmetic.h"

int main() {
    const LongNum f = 2.0_bigF / 3.0_bigF;
    const LongNum f1 = f + 10000.0_bigF;
    std::cout << f;
    return 0;
}
