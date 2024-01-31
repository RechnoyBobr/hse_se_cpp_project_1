#include <iostream>
#include "long_arithmetic.h"

std::string operator ""_bigF(const char *x, long unsigned int k) {
    return std::string{x};
}

int main() {
    std::string f_ = "124.12"_bigF;
    const LongNum f(f_, 9);
    LongNum f3 = f;
    f3.cout();
    return 0;
}
