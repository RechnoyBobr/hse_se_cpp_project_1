#include <iostream>
#include "long_arithmetic.h"

int main() {
    const LongNum f(124125.575253421, 9), f1(1450.6437525, 7);
    LongNum f3 = f * f1;
    f3.cout();
    return 0;
}
