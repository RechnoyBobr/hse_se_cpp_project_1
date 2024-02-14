#include <iostream>
#include "../include/long_arithmetic.h"

long_num::LongNum pie(int accuracy) {
    int iters = accuracy - 20;
    clock_t t_1 = clock();
    long_num::LongNum p = 0.0_bigF, n1 = 0.2_bigF, n2 = (239.0_bigF).inverse_number(accuracy), d = 1.0_bigF;
    long_num::LongNum mult1 = n1 * n1, mult2 = n2 * n2, four = 4.0_bigF, x, x1, x2;
    for (int i = 0; i < iters; ++i) {
        x = four * n1;
        x1 = x - n2;
        x2 = x1 / d;
        //std::cout << p << " " << x << " " << x1 << " " << x2 << "\n";
        if (i % 2 == 0) {
            p += x2;
        } else {
            p -= x2;
        }
        p.strip(accuracy + 150);
        n1 = n1 * mult1;
        n2 = n2 * mult2;
        n1.strip(accuracy + 150);
        n2.strip(accuracy + 150);

        d += 2.0_bigF;

    }
    // At this moment it returns pi/4, so we have to multiply by four
    p = p * four;
    clock_t t_2 = clock();
    std::cout << "Time used to calculate pi: " << 1000 * (t_2 - t_1) / CLOCKS_PER_SEC << "ms\n";
    p.strip(accuracy);
    return p;
}



int main() {
    long_num::LongNum pi = pie(100);
    std::cout << "Calculated pie is: " << pi << "\n";
}