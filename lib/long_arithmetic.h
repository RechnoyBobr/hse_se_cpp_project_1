#ifndef long_num
#define long_num
#include <deque>

class LongNum {
    std::deque<long long> int_part;
    // numbers closer to the beginning is less than the ones that closer to end i_part[0] < i_part[1]
    std::deque<long long> float_part;
    int n_frac;
    // numbers closer to the beginning is less than the ones that closer to end f_part[0] < f_part[1]
    const int BASE = 1000000;
    bool isNegative;

public:
    LongNum();

    LongNum(float num, int accuracy);

    void cout() const; // Cout the whole number
    LongNum operator+(const LongNum &n) const;
    LongNum operator*(const LongNum &n) const;
    LongNum operator-(const LongNum &n) const;
    LongNum operator>(const LongNum &n) const;
    LongNum operator<(const LongNum &n) const;
    LongNum operator==(const LongNum &n) const;
    LongNum& operator=(const LongNum &n);
    LongNum operator>=(const LongNum &n) const;
    LongNum operator<=(const LongNum &n) const;
};


#endif
