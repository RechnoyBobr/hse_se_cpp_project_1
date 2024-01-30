#include "long_arithmetic.h"
#include <cmath>
#include <deque>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <deque>

LongNum::LongNum() {
    float_part = std::deque<long long>(0);
    int_part = std::deque<long long>(0);
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
    n_frac = accuracy;
    long long rounder = pow(10, accuracy + 1);
    num = round((num * rounder + 0.5)) / static_cast<float>(rounder);
    int_part.resize(size_Z / 6 + (size_Z % 6 ? 1 : 0));
    float_part.resize(accuracy / 6 + (accuracy % 6 ? 1 : 0));
    double integral;
    float fractional = modf(num, &integral);
    auto i_ptr = int_part.begin();
    auto f_ptr = float_part.begin();

    while (integral >= 1e-6) {
        *i_ptr = static_cast<int>(integral) % BASE;
        ++i_ptr;
        integral = static_cast<double>(static_cast<int>(integral) / BASE);
    }
    modf(fractional * static_cast<int>(pow(10, accuracy)), &integral);

    while (accuracy < 6) {
        integral *= 10;
        accuracy++;
    }
    while (integral >= 1e-6) {
        if (f_ptr == float_part.begin() && accuracy >= 7) {
            int size = static_cast<int>(log10(integral)) + 1;
            if (size % 6 != 0) {
                *f_ptr = static_cast<int>(integral) % static_cast<int>(pow(10, size % 6));
                integral = static_cast<double>(static_cast<int>(integral) / static_cast<int>(pow(10, size % 6)));
            } else {
                *f_ptr = static_cast<int>(integral) % BASE;
                integral = static_cast<double>(static_cast<int>(integral) / BASE);
            }
        } else {
            *f_ptr = static_cast<int>(integral) % BASE;
            integral = static_cast<double>(static_cast<int>(integral) / BASE);
        }
        ++f_ptr;
    }
}

LongNum LongNum::operator>(const LongNum &n) const {
    auto ptr_1 = int_part.end();
    auto ptr_2 = n.int_part.end();
    while (ptr_1 != int_part.begin() && ptr_2 != n.int_part.begin()) {
        --ptr_1;
        --ptr_2;
        if (*ptr_1 > *ptr_2) {
            return true;
        }
        if (*ptr_1 < *ptr_2) {
            return false;
        }
    }
    if (ptr_2 != n.int_part.begin()) {
        return false;
    }
    if (ptr_1 != int_part.begin()) {
        return true;
    }
    ptr_1 = float_part.end();
    ptr_2 = n.float_part.end();
    while (ptr_1 != float_part.begin()) {
        --ptr_1;
        --ptr_2;
        if (*ptr_1 > *ptr_2) {
            return true;
        }
        if (*ptr_1 < *ptr_2) {
            return false;
        }
    }
    if (ptr_2 != n.float_part.begin()) {
        return false;
    }
    if (ptr_1 != float_part.begin()) {
        return true;
    }
    return false;
}

LongNum LongNum::operator<(const LongNum &n) const {
    auto ptr_1 = int_part.end();
    auto ptr_2 = n.int_part.end();
    while (ptr_1 != int_part.begin() && ptr_2 != n.int_part.begin()) {
        --ptr_1;
        --ptr_2;
        if (*ptr_1 < *ptr_2) {
            return true;
        }
        if (*ptr_1 > *ptr_2) {
            return false;
        }
    }
    if (ptr_2 != n.int_part.begin()) {
        return true;
    }
    if (ptr_1 != int_part.begin()) {
        return false;
    }
    ptr_1 = float_part.end();
    ptr_2 = n.float_part.end();
    while (ptr_1 != float_part.begin()) {
        --ptr_1;
        --ptr_2;
        if (*ptr_1 < *ptr_2) {
            return true;
        }
        if (*ptr_1 > *ptr_2) {
            return false;
        }
    }
    if (ptr_2 != n.float_part.begin()) {
        return true;
    }
    if (ptr_1 != float_part.begin()) {
        return false;
    }
    return false;
}

LongNum LongNum::operator==(const LongNum &n) const {
    if (!(this < *n) && !(this > *n)) {
        return true;
    }
    return false;
}

LongNum LongNum::operator>=(const LongNum &n) const {
    if (this > *n || this == *n) {
        return true;
    }
    return false;
}

LongNum LongNum::operator<=(const LongNum &n) const {
    if (this < *n || this == *n) {
        return true;
    }
    return false;
}

LongNum &LongNum::operator=(const LongNum &n) {
    std::copy(n.float_part.begin(), n.float_part.end(), float_part);
    std::copy(n.int_part.begin(), n.int_part.end(), int_part);
    this->isNegative = n.isNegative;
    this->n_frac = n.n_frac;
    return *this;
}


LongNum LongNum::operator+(const LongNum &n) const {
    if (n.isNegative && !this->isNegative) {
        LongNum res = *n - this;
        res.isNegative = true;
        return res;
    }
    if (!n.isNegative && this->isNegative) {
        LongNum res = *n - this;
        res.isNegative = false;
        return res;
    }

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
        if (*f_ptr >= BASE) {
            if (f_ptr == res.float_part.end() - 1) {
                to_int_part = true;
                *f_ptr %= BASE;
            } else {
                *(f_ptr + 1) += 1;
                *f_ptr %= BASE;
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
            *i_ptr += 1;
            to_int_part = false;
        }
        if (ind < int_part.size()) {
            *i_ptr += int_part[ind];
        }
        if (ind < n.int_part.size()) {
            *i_ptr += n.int_part[ind];
        }
        if (*i_ptr >= BASE) {
            if (i_ptr == res.int_part.end() - 1) {
                res.int_part.emplace_back();
            }
            *(i_ptr + 1) = 1;
            *i_ptr %= BASE;
        }
        ++i_ptr;
        ++ind;
    }
    return res;
}

LongNum LongNum::operator-(const LongNum &n) const {
    const unsigned long float_size =
            std::max(float_part.size(), n.float_part.size());
    const unsigned long int_size = std::max(int_part.size(), n.int_part.size());
    LongNum res, n1, n2;
    if (*n > this) {
        res.isNegative = true;
        n1 = *n;
        n2 = *this;
    } else {
        n1 = *this;
        n2 = *n;
    }
    int diff = float_part.size() - n.float_part.size();
    res.float_part.resize(float_size);
    res.int_part.resize(int_size);
    bool to_int_part = false;
    auto f_ptr = res.float_part.begin();
    auto f_ptr1 = n1.float_part.begin();
    auto f_ptr2 = n2.float_part.begin();

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
            *f_ptr -= *f_ptr2;
            ++f_ptr2;
            if (diff != 0) {
                increase = true;
            }
        }
        if (*f_ptr < 0) {
            if (f_ptr == res.float_part.end() - 1) {
                to_int_part = true;
                *f_ptr += BASE;
            } else {
                *(f_ptr - 1) -= 1;
                *f_ptr += BASE;
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
            *i_ptr -= 1;
            to_int_part = false;
        }
        if (ind < int_part.size()) {
            *i_ptr += int_part[ind];
        }
        if (ind < n.int_part.size()) {
            *i_ptr += n.int_part[ind];
        }
        if (*i_ptr >= BASE) {
            if (i_ptr == res.int_part.end() - 1) {
                res.int_part.emplace_back();
            }
            *(i_ptr + 1) = 1;
            *i_ptr %= BASE;
        }
        ++i_ptr;
        ++ind;
    }
    return res;
}


LongNum LongNum::operator*(const LongNum &n) const {
    LongNum res;
    res.n_frac = n_frac + n.n_frac;
    int remainder = 0;
    int last_elem_size = res.n_frac % 6;
    const unsigned long size_int = int_part.size() + n.int_part.size() - 1;
    res.int_part.resize(size_int);
    res.float_part.resize((n_frac + n.n_frac) / 6 + ((n_frac + n.n_frac) % 6 ? 1 : 0));
    for (int i = 0; i < n.float_part.size() + n.int_part.size(); ++i) {
        for (int j = 0; j < float_part.size() + int_part.size(); ++j) {
            if (i + j < res.float_part.size()) {
                if (i + j == 0) {
                    res.float_part[0] = n.float_part[i] * float_part[j];
                    while (res.float_part[0] % 10 == 0 && res.float_part[0] != 0) {
                        res.float_part[0] /= 10;
                    }
                    remainder = res.float_part[0] / static_cast<int>(pow(10, last_elem_size));
                    res.float_part[0] %= static_cast<int>(pow(10, last_elem_size));
                    while (static_cast<int>(log10(res.float_part[0])) != 5) {
                        res.float_part[0] *= 10;
                    }
                } else {
                    res.float_part[i + j] += n.float_part[i] * float_part[j];
                    remainder = res.float_part[i + j] / BASE;
                    res.float_part[i + j] %= BASE;
                }
                res.float_part[i + j + 1] += remainder;
                remainder = 0;
            } else {
                if (i >= n.float_part.size() && j >= float_part.size()) {
                    res.int_part[i + j - res.float_part.size()] += n.int_part[i - n.float_part.size()] * int_part[
                        j - float_part.size()];
                } else if (i < n.float_part.size()) {
                    res.int_part[i + j - res.float_part.size()] += n.float_part[i] * int_part[j - float_part.size()];
                } else {
                    res.int_part[i + j - res.float_part.size()] += n.int_part[i - n.float_part.size()] * float_part[j];
                }
                remainder = res.int_part[i + j - res.float_part.size()] / BASE;
                res.int_part[i + j - res.float_part.size()] %= BASE;
                if (i + j + 1 - res.float_part.size() >= res.int_part.size()) {
                    res.int_part.emplace_back();
                }
                res.int_part[i + j + 1 - res.float_part.size()] += remainder;
            }
        }
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
        long long size = static_cast<long long>(log10(*f_ptr));
        if (f_ptr == float_part.begin()) {
            long long divider = static_cast<long long>(pow(10, n_frac % 6));
            std::cout << *f_ptr / divider;
        } else {
            if (size != 5) {
                for (int i = 0; i < 5 - size; ++i) {
                    std::cout << '0';
                }
                std::cout << *f_ptr;
            }
        }
    }
}
