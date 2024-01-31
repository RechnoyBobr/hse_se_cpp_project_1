#include <iostream>
#include "long_arithmetic.h"

LongNum operator ""_bigF(const char *x) {
    return {std::string{x}};
}

int main() {

    LongNum f = 13352315653.12356123612_bigF;
    LongNum g = f *1.0_bigF;
    g.cout();
    return 0;
}
