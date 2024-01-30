#include "long_arithmetic.h"
#include <cmath>
#include <deque>
#include <iostream>
#include <string>
#include <algorithm>
#include <deque>

LongNum::LongNum() {
    float_part = std::deque<int>(0);
    int_part = std::deque<int>(0);
    isNegative = false;
}

LongNum::LongNum(float num, int accuracy = 20) {
    const int size_Z = std::ranges::max(static_cast<int>(log10f(num)), 0) + 1;
    if (num < 0) {
        isNegative = true;
        num = -num;
    } else {
        isNegative = false;
    }
    long long rounder = pow(10, accuracy + 1);
    num = round((num * rounder+0.5)) / static_cast<float>(rounder);
    int_part.resize(size_Z / 6 + (size_Z % 6 ? 1 : 0));
    float_part.resize(accuracy / 6 + (accuracy % 6 ? 1 : 0));
    double integral;
    float fractional = modf(num, &integral);
    auto i_ptr = int_part.begin();
    auto f_ptr = float_part.begin();

    while (integral >= 1e-6) {
        *i_ptr = static_cast<int>(integral) % 1000000;
        ++i_ptr;
        integral = static_cast<double>(static_cast<int>(integral) / 1000000);
    }
    modf(fractional * static_cast<int>(pow(10, accuracy)), &integral);

    while (accuracy < 6) {
        integral *= 10;
        accuracy++;
    }
    while (integral >= 1e-6) {
        if (f_ptr == float_part.begin() && accuracy >= 7) {
            int size = static_cast<int>(log10f(integral)) + 1;
            if (size % 6 != 0) {
                *f_ptr = static_cast<int>(integral) % static_cast<int>(pow(10, size % 6));
                integral = static_cast<double>(static_cast<int>(integral) / static_cast<int>(pow(10, size % 6)));
            } else {
                *f_ptr = static_cast<int>(integral) % 1000000;
                integral = static_cast<double>(static_cast<int>(integral) / 1000000);
            }
        } else {
            *f_ptr = static_cast<int>(integral) % 1000000;
            integral = static_cast<double>(static_cast<int>(integral) / 1000000);
        }
        ++f_ptr;
    }
}

LongNum LongNum::operator+(const LongNum &n) const {
    const unsigned long float_size =
            std::max(float_part.size(), n.float_part.size());
    const unsigned long int_size = std::max(int_part.size(), n.int_part.size());
    LongNum res;
    int diff = float_part.size() - n.float_part.size();
    res.float_part.resize(float_size);
    res.int_part.resize(int_size);
    bool to_int_part = false;
    auto f_ptr = res.float_part.begin();
    auto f_ptr1 = float_part.begin();
    auto f_ptr2 = n.float_part.begin();

    while (f_ptr != res.float_part.end()) {
        bool decrease = false, increase = false;
        if (f_ptr1 != float_part.end() && diff >= 0) {
            *f_ptr += *f_ptr1;
            ++f_ptr1;
            if (diff != 0) {
                decrease = true;
            }
        }
        if (f_ptr2 != n.float_part.end() && diff <= 0) {
            *f_ptr += *f_ptr2;
            ++f_ptr2;
            if (diff != 0) {
                increase = true;
            }
        }
        if (*f_ptr >= 1000000) {
            if (f_ptr == res.float_part.end()) {
                to_int_part = true;
                *f_ptr %= 1000000;
            } else {
                *(f_ptr + 1) += 1;
                *f_ptr %= 1000000;
            }
        }
        if (increase) {
            diff++;
        }
        if (decrease) {
            diff--;
        }
        ++f_ptr;
    }
    auto i_ptr = res.int_part.begin();
    int ind = 0;
    while (i_ptr != res.int_part.end()) {
        if (to_int_part) {
            *i_ptr = 1;
            to_int_part = false;
        }
        if (ind < int_part.size()) {
            *i_ptr += int_part[ind];
        }
        if (ind < n.int_part.size()) {
            *i_ptr += n.int_part[ind];
        }
        if (*i_ptr >= 1000000) {
            if (i_ptr == res.int_part.end() - 1) {
                res.int_part.emplace_back();
            }
            *(i_ptr + 1) = 1;
            *i_ptr %= 1000000;
        }
        ++i_ptr;
        ++ind;
    }
    return res;
}

void LongNum::cout() const {
    if (isNegative) {
        std::cout << '-';
    }
    auto i_ptr = int_part.end();
    while (i_ptr != int_part.begin()) {
        --i_ptr;
        std::cout << *i_ptr;
    }
    std::cout << '.';
    auto f_ptr = float_part.end();
    while (f_ptr != float_part.begin()) {
        --f_ptr;
        std::cout << *f_ptr;
    }
}
