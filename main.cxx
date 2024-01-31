#include <iostream>
#include "long_arithmetic.h"

LongNum operator ""_bigF(const char *x) {
    return {std::string{x}};
}

int main() {
    const LongNum f = 1.241_bigF, f1 = 648.1_bigF;
    LongNum f3 = f * f1;
    f3.cout();
    return 0;
}
