#include <iostream>
#include "long_arithmetic.h"

LongNum operator ""_bigF(const char *x) {
    return {std::string{x}};
}

int main() {
    LongNum f = 1.3425_bigF;
    LongNum g = f * 1.1_bigF;
    g.cout();
    (1255.1_bigF * 5125124.512562_bigF).cout();
    return 0;
}
