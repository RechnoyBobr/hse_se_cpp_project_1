#ifndef LINT
#define LINT
#include <deque>

class LongNum {
    std::deque<int> int_part;
    // numbers closer to the beginning is less than the ones that closer to end i_part[0] < i_part[1]
    std::deque<int> float_part;
    // numbers closer to the beginning is less than the ones that closer to end f_part[0] < f_part[1]
    const int BASE = 7;
    bool isNegative;

public:
    LongNum();

    LongNum(float num, int accuracy);

    void cout() const; // Cout the whole number
    LongNum operator+(const LongNum &n) const;
    LongNum operator-(const LongNum &n) const;
};


#endif
