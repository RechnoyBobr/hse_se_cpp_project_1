#include "long_arithmetic.h"
#include <cmath>
#include <deque>
#include <iostream>
#include <algorithm>

LongNum::LongNum() {
    exp = 0;
    digits = std::deque<long long>(0);
    isNegative = false;
}

LongNum LongNum::operator-() {
    this->isNegative = !this->isNegative;
    return *this;
}

LongNum::LongNum(std::string num) {
    digits.resize((num.size() - 1) / 6 + ((num.size() - 1) % 6 ? 1 : 0));
    if (num[0] == '-') {
        this->isNegative = true;
        num = num.substr(1, num.size() - 1);
    } else {
        this->isNegative = false;
    }
    int n = 0;
    auto ptr = digits.begin();
    for (int i = 0; i < num.size(); ++i) {
        if (num[i] == '.') {
            exp = i - 1;
            continue;
        }
        if (n * 10 < BASE) {
            n *= 10;
            n += num[i] - '0';
        } else {
            *ptr = n;
            n = 0;
            ++ptr;
        }
    }
    while (n * 10 < BASE) {
        n *= 10;
    }
    *ptr = n;
}


void LongNum::inverse_sign() {
    this->isNegative = !this->isNegative;
}

bool LongNum::operator>(const LongNum &n) const {
    if (this->exp > n.exp) {
        return true;
    }
    if (this->exp < n.exp) {
        return false;
    }
    for (int i = 0; i < this->digits.size(); i++) {
        if (this->digits[i] > n.digits[i]) {
            return true;
        }
        if (this->digits[i] < n.digits[i]) {
            return false;
        }
    }
    return false;
}

bool LongNum::operator<(const LongNum &n) const {
    if (this->exp < n.exp) {
        return true;
    }
    if (this->exp > n.exp) {
        return false;
    }
    for (int i = 0; i < this->digits.size(); i++) {
        if (this->digits[i] < n.digits[i]) {
            return true;
        }
        if (this->digits[i] > n.digits[i]) {
            return false;
        }
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
    this->isNegative = n.isNegative;
    this->digits = std::deque(n.digits.begin(), n.digits.end());
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
    res.isNegative = (n.isNegative + this->isNegative) % 2;
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
    return res;
}

std::string LongNum::toStr() const {
    std::string result;
    if (isNegative) {
        result += '-';
    }
    for (int i = 0; i < digits.size(); ++i) {
        if (i != digits.size() - 1) {
            result += std::to_string(digits[i]);
        } else {
            int temp = digits[i];
            while (temp % 10 == 0) {
                temp /= 10;
            }
            result += std::to_string(temp);
        }
    }
    result = result.substr(0, exp + 2) + '.' + result.substr(exp + 1, result.size());
    return result;
}


std::ostream &operator<<(std::ostream &out, const LongNum &n) {
    out << n.toStr();
    return out;
}
