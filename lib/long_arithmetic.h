#pragma once
#include <deque>
#include <string>


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

    LongNum(std::string, int accuracy);

    void inverse_sign();

    void cout() const; // Cout the whole number
    LongNum operator+(const LongNum &n) const;

    LongNum operator*(const LongNum &n) const;

    LongNum operator-(const LongNum &n) const;

    bool operator>(const LongNum &n) const;

    bool operator<(const LongNum &n) const;

    bool operator==(const LongNum &n) const;

    LongNum &operator=(const LongNum &n);

    bool operator>=(const LongNum &n) const;

    bool operator<=(const LongNum &n) const;
};
