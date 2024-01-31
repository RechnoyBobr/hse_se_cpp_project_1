#include <iostream>
#include "long_arithmetic.h"

LongNum operator ""_bigF(const char *x) {
    return {std::string{x}};
}

int main() {
    const LongNum f = 124.12_bigF, f1 = 3243.1234452366346_bigF;
    LongNum f3 = f + f1;
    f.cout();
    return 0;
}
