#include "long_arithmetic.h"
#include <cmath>
#include <deque>
#include <iostream>
#include <algorithm>

LongNum::LongNum() {
    float_part = std::deque<long long>(0);
    int_part = std::deque<long long>(0);
    isNegative = false;
}


LongNum::LongNum(std::string num) {
    int size = 0;
    if (num[0] == '-') {
        this->isNegative = true;
        num = num.substr(1, num.size() - 1);
    } else {
        this->isNegative = false;
    }
    for (int i = 0; i < num.size(); ++i) {
        if (num[i] == '.') {
            size = i;
            break;
        }
    }
    int_part.resize(size / 6 + (size % 6 ? 1 : 0));
    if (size == 0) {
        size++;
    }
    auto i_ptr = int_part.begin();
    int i = size - 1;
    while (i >= 0) {
        int temp_n = 0, to_add = 6;
        if (i == size - 1) {
            to_add = size % 6;
        }
        for (int j = to_add - 1; j >= 0; --j) {
            temp_n *= 10;
            temp_n += num[i - j] - '0';
        }
        *i_ptr = temp_n;
        i -= to_add;
        ++i_ptr;
    }
    float_part.resize((num.size() - size - 1) / 6 + ((num.size() - size - 1) % 6 ? 1 : 0));
    auto f_ptr = float_part.begin();
    int from = num.size() - 1;
    this->n_frac = from;
    while (from > size) {
        int to_add = 6;
        int temp_n = 0;
        if (from == num.size() - 1 && (from - size) % 6 != 0) {
            to_add = (from - size) % 6;
        }
        for (int k = to_add - 1; k >= 0; --k) {
            temp_n *= 10;
            temp_n += num[from - k] - '0';
        }
        while (to_add < 6) {
            temp_n *= 10;
            to_add++;
        }
        *f_ptr = temp_n;
        ++f_ptr;
        from -= 6;
    }
}


void LongNum::inverse_sign() {
    this->isNegative = !this->isNegative;
}

bool LongNum::operator>(const LongNum &n) const {
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

bool LongNum::operator<(const LongNum &n) const {
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

bool LongNum::operator==(const LongNum &n) const {
    if (!(*this < n) && !(*this > n)) {
        return true;
    }
    return false;
}

bool LongNum::operator>=(const LongNum &n) const {
    if (*this > n || *this == n) {
        return true;
    }
    return false;
}

bool LongNum::operator<=(const LongNum &n) const {
    if (*this < n || *this == n) {
        return true;
    }
    return false;
}

LongNum &LongNum::operator=(const LongNum &n) {
    this->float_part = std::deque(n.float_part.begin(), n.float_part.end());
    this->int_part = std::deque(n.int_part.begin(), n.int_part.end());
    this->isNegative = n.isNegative;
    this->n_frac = n.n_frac;
    return *this;
}


LongNum LongNum::operator+(const LongNum &n) const {
    if (n.isNegative && !this->isNegative) {
        LongNum n1 = n;
        n1.inverse_sign();
        LongNum res = *this - n1;
        return res;
    }
    if (!n.isNegative && this->isNegative) {
        LongNum n1 = *this;
        n1.inverse_sign();
        LongNum res = n - n1;
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


LongNum LongNum::operator-(const LongNum &number) const {
    LongNum res;
    LongNum n = number;
    if (this->isNegative && !n.isNegative) {
        n.inverse_sign();
        res = *this + n;
    }
    const unsigned long float_size =
            std::max(float_part.size(), n.float_part.size());
    const unsigned long int_size = std::max(int_part.size(), n.int_part.size());
    LongNum n1, n2;
    if (n > *this) {
        res.isNegative = true;
        n1 = number;
        n2 = *this;
    } else {
        n1 = *this;
        n2 = number;
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
                *(f_ptr + 1) -= 1;
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
            *i_ptr -= n.int_part[ind];
        }
        if (*i_ptr < 0) {
            *(i_ptr + 1) = -1;
            *i_ptr += BASE;
        }
        ++i_ptr;
        ++ind;
    }
    return res;
}

// TODO: fix multiplying
LongNum LongNum::operator*(const LongNum &n) const {
    LongNum res;

    res.int_part.resize(int_part.size() + n.int_part.size());
    res.float_part.resize(float_part.size() + n.float_part.size());
    for (int i = 0; i < this->float_part.size() + this->int_part.size(); ++i) {
        for (int j = 0; j < n.float_part.size() + n.int_part.size(); ++j) {
            long long remainder = 0;
            size_t ind = i + j;
            long long n1, n2;
            if (i >= this->float_part.size()) {
                n1 = int_part[i - float_part.size()];
            } else {
                n1 = float_part[i];
            }
            if (j >= n.float_part.size()) {
                n2 = n.int_part[j - n.float_part.size()];
            } else {
                n2 = n.float_part[j];
            }

            if (i + j < res.float_part.size()) {
                res.float_part[ind] = n1 * n2;
                if (ind == res.float_part.size() - 1) {
                    res.int_part[0] += res.float_part[ind] / BASE;
                } else {
                    res.float_part[ind + 1] += res.float_part[ind] / BASE;
                }
                res.float_part[ind] %= BASE;
            } else {
                ind -= res.float_part.size();
                res.int_part[ind] = n1 * n2;
                res.int_part[ind + 1] += res.float_part[ind] / BASE;
                res.float_part[ind] %= BASE;
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
        if (f_ptr != float_part.end() - 1) {
            while (size != 5) {
                std::cout << "0";
                size++;
            }
            std::cout << *f_ptr;
        } else {
            std::cout << *f_ptr;
        }
    }
}
