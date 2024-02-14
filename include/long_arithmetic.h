#pragma once

#include <deque>
#include <string>

class LongNum {
public:
    LongNum();

    /*explicit*/ LongNum(const std::string &num); // NOLINT(*-explicit-constructor)

    void inverse_sign();

    [[nodiscard]] std::string toStr() const; // Returns number as string

    LongNum operator+(const LongNum &n) const;

    LongNum operator*(const LongNum &n) const;

    void operator+=(const LongNum &n);

    void operator-=(const LongNum &n);

    LongNum operator-(const LongNum &n) const;

    LongNum operator-();
    void strip(int n);
    [[nodiscard]] LongNum inverse_number(int accuracy) const;

    LongNum operator/(const LongNum &n) const;

    bool operator>(const LongNum &n) const;

    bool operator<(const LongNum &n) const;

    bool operator==(const LongNum &n) const;

    bool operator!=(const LongNum &n) const;


    LongNum &operator=(const LongNum &n);


    bool operator>=(const LongNum &n) const;

    bool operator<=(const LongNum &n) const;

    friend std::ostream &operator<<(std::ostream &out, const LongNum &n);
private:
    std::deque<long long> digits;
    long expPos;
    // numbers closer to the beginning is less than the ones that closer to end
    // f_part[0] < f_part[1]
    const long long BASE = 1000000000;
    const int BASE_SIZE = 9;
    bool isNegative;

};

LongNum operator ""_bigF(const char *x);

LongNum pie(int accuracy);
void test_pie(LongNum pi);