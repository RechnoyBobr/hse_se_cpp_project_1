#include "long_arithmetic.h"
#include <cmath>
#include <deque>
#include <iostream>
#include <algorithm>

std::deque<long long> merge_deques(const std::deque<long long> &int_part, const std::deque<long long> &float_part) {
    /*Deque's element is 6 digit of the whole number. Main part of merging deques is making sure that last integer part
     *of number will be filled to 6 digits with fractional digits*/
    std::deque<long long> res = std::deque(int_part.begin(), int_part.end());
    std::deque floats = std::deque(float_part.begin(), float_part.end());
    std::reverse(res.begin(), res.end());
    int size = static_cast<int>(log10(static_cast<double>(res[res.size() - 1] ? res[res.size() - 1] : 1)));
    int diff = 5 - size;
    auto ptr = res.end() - 1;
    if (diff != 0) {
        for (int i = 0; i < floats.size(); ++i) {
            res.emplace_back();
            *ptr *= pow(10, diff);
            *ptr += floats[i] / pow(10, 6 - diff);
            floats[i] %= static_cast<long long>(pow(10, 6 - diff));
            ++ptr;
            *ptr = floats[i];
        }
    }
    if (res[res.size() - 1] == 0) {
        size = 1;
    } else {
        size = static_cast<int>(log10(res[res.size() - 1]));
    }
    if (size != 5) {
        *(res.end() - 1) *= pow(10, 5 - size);
    }
    return res;
}

void LongNum::unmerge_deques() {
    int f_size = static_cast<int>(log10f(digits[0] ? digits[0] : 1)) + 1;
    int ind = (this->dotPos - f_size) / 6 + ((this->dotPos - f_size) > 0 ? 1 : 0);
    int digit = ind == 0 ? dotPos : (this->dotPos - f_size - 1) % 6;
    int_part = std::deque(digits.begin(), digits.begin() + ind);
    if (digit != 0) {
        int_part.emplace_back(digits[ind] / pow(10, 6 - digit % 6));
    }
    std::reverse(int_part.begin(), int_part.end());
    float_part = std::deque(digits.begin() + ind, digits.end());
    float_part[0] %= static_cast<long long>(pow(10, 6 - digit % 6));
    float_part[0] *= pow(10, digit % 6);
    for (int i = 1; i < float_part.size() - 1; ++i) {
        float_part[i - 1] += float_part[i] / static_cast<long long>(pow(10, 6 - digit % 6));
        float_part[i] %= static_cast<long long>(pow(10, 6 - digit % 6));
        float_part[i] *= static_cast<long long>(pow(10, digit % 6));
    }
}

LongNum::LongNum() {
    float_part = std::deque<long long>(0);
    int_part = std::deque<long long>(0);
    digits = std::deque<long long>(0);
    n_frac = 0;
    dotPos = 0;
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
    dotPos = size;
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
    int from = size + 1;
    this->n_frac = from;
    while (from <= num.size() - 1) {
        int to_add = 6;
        int temp_n = 0;
        if (from > static_cast<int>(num.size() - 6) && (num.size() - size) % 6 != 0) {
            to_add = (num.size() - size - 1) % 6;
        }
        for (int k = 0; k < to_add; ++k) {
            temp_n *= 10;
            temp_n += static_cast<int>(num[from + k] - '0');
        }
        while (to_add < 6) {
            temp_n *= 10;
            to_add++;
        }
        *f_ptr = temp_n;
        ++f_ptr;
        from += 6;
    }
    digits.resize((num.size() - 2) / 6 + ((num.size() - 2) % 6 ? 1 : 0));
    digits = merge_deques(int_part, float_part);
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
    LongNum n_1 = *this;
    if (this->isNegative && !n.isNegative) {
        n_1.inverse_sign();
        res = n_1 + n;
        return res;
    }
    if (!this->isNegative && n.isNegative) {
        n.inverse_sign();
        res = n + n_1;
        return res;
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


LongNum LongNum::operator*(const LongNum &n) const {
    LongNum res;
    res.isNegative = n.isNegative * this->isNegative;
    const std::deque<long long> number_1 = this->digits, number_2 = n.digits;
    std::deque<long long> res_number(number_1.size() + number_2.size() + 1);
    for (int i = static_cast<int>(number_1.size()) - 1; i >= 0; --i) {
        int carry = 0;
        for (int j = static_cast<int>(number_2.size()) - 1; j >= 0 || carry != 0; --j) {
            long long cur = res_number[i + j + 1] +
                            number_1[i] * (j >= 0 ? number_2[j] : 0) + carry;
            res_number[i + j + 1] = cur % BASE;
            carry = static_cast<int>(cur / BASE);
        }
    }
    if (*(res_number.end() - 1) == 0) {
        res_number.pop_back();
    }
    if (*res_number.begin() == 0) {
        res_number.pop_front();
    }
    res.digits = res_number;
    res.dotPos = this->dotPos + n.dotPos;
    res.unmerge_deques();
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
    auto f_ptr = float_part.begin();
    while (f_ptr != float_part.end()) {

        long long size;
        if (*f_ptr == 0) {
            size = 1;
        } else {
            size = static_cast<long long>(log10(*f_ptr));
        }
        if (f_ptr != float_part.end() - 1) {
            while (size != 5) {
                std::cout << "0";
                size++;
            }
            std::cout << *f_ptr;
        } else {
            std::cout << *f_ptr;
        }
        ++f_ptr;
    }
    std::cout << "\n";
}
