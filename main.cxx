#include <iostream>
#include "long_arithmetic.h"

LongNum operator ""_bigF(const char *x) {
    return {std::string{x}};
}

int main() {
    const LongNum f = -1.3425_bigF;
    std::cout << f;
    return 0;
}
