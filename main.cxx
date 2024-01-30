#include <iostream>
#include "long_arithmetic.h"
int main() {
    const LongNum f(12.412334, 6), f1(143.09, 3);
    LongNum f3 = f + f1;
    f3.cout();
    return 0;
}
