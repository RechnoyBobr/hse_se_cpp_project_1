#include <iostream>
#include "long_arithmetic.h"
int main() {
    const LongNum f(0.573421, 6), f1(10.645, 3);
    LongNum f3 = f + f1;
    f3.cout();
    return 0;
}
