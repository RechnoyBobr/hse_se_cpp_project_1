#include "long_arithmetic.h"
#include <algorithm>
#include <deque>
#include <iostream>
#include <cmath>
#include <string>

LongNum::LongNum() {
    expPos = 0;
    digits = std::deque<long long>(0);
    isNegative = false;
}

LongNum LongNum::operator-() {
    this->isNegative = !this->isNegative;
    return *this;
}

LongNum::LongNum(const std::string &num) {
    int i = 0;
    isNegative = false; // _bigF operator don't recognize - as a char, but as a
    // unary operator.
    while (i < num.size() && num[i] != '.') {
        i++;
    }
    expPos = i / 6 + (i % 6 ? 1 : 0);
    digits.resize(i / 6 + (i % 6 ? 1 : 0));
    auto int_end = digits.end(); // std::deque<long long>:iterator;
    int block = i - 1;
    while (int_end != digits.begin()) {
        --int_end;
        int to = block - 5;
        int n = 0, mp = 1;
        for (; block >= std::max(to, 0); block--) {
            n += (num[block] - '0') * mp;
            mp *= 10;
        }
        *int_end = n;
        to = block - 1;
    }
    digits.resize(digits.size() + (num.size() - i - 1) / 6 +
                  ((num.size() - i - 1) % 6 ? 1 : 0));
    block = i + 1;
    auto frac = digits.begin() + i / 6 + (i % 6 ? 1 : 0);

    while (frac != digits.end()) {
        int to = block + 5, n = 0, cnt = 0;
        for (; block <= std::min(to, static_cast<int>(num.size()) - 1); ++block) {
            n *= 10;
            n += num[block] - '0';
            cnt++;
        }
        if (block == num.size() && n != 0) {
            while (cnt < 6) {
                n *= 10;
                cnt++;
            }
        }
        *frac = n;
        to = block + 1;
        ++frac;
    }
}

void LongNum::inverse_sign() { this->isNegative = !this->isNegative; }

bool LongNum::operator>(const LongNum &n) const {
    if (this->expPos > n.expPos) {
        return true;
    }
    if (this->expPos < n.expPos) {
        return false;
    }
    for (int i = 0; i < std::min(this->digits.size(), n.digits.size()); i++) {
        if (this->digits[i] > n.digits[i]) {
            return true;
        }
        if (this->digits[i] < n.digits[i]) {
            return false;
        }
    }
    if (digits.size() > n.digits.size()) {
        for (int i = static_cast<int>(n.digits.size()); i < digits.size(); ++i) {
            if (digits[i] != 0) {
                return true;
            }
        }
    } else if (digits.size() > n.digits.size()) {
        for (int i = static_cast<int>(digits.size()); i < n.digits.size(); ++i) {
            if (n.digits[i] != 0) {
                return false;
            }
        }
    }
    return false;
}

bool LongNum::operator<(const LongNum &n) const {
    if (this->expPos < n.expPos) {
        return true;
    }
    if (this->expPos > n.expPos) {
        return false;
    }
    for (int i = 0; i < std::min(this->digits.size(), n.digits.size()); i++) {
        if (this->digits[i] < n.digits[i]) {
            return true;
        }
        if (this->digits[i] > n.digits[i]) {
            return false;
        }
    }
    if (digits.size() > n.digits.size()) {
        for (int i = n.digits.size(); i < digits.size(); ++i) {
            if (digits[i] != 0) {
                return false;
            }
        }
    } else if (digits.size() > n.digits.size()) {
        for (int i = digits.size(); i < n.digits.size(); ++i) {
            if (n.digits[i] != 0) {
                return true;
            }
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
    LongNum res;
    res.digits.resize(std::max(this->digits.size(), n.digits.size()));
    res.expPos = std::max(this->expPos, n.expPos);
    auto n1_ptr =
            this->digits.end() - 1; // std::deque<long long>::reverse_iterator
    auto n2_ptr = n.digits.end() - 1;
    long diff = this->digits.size() - this->expPos - n.digits.size() + n.expPos;
    bool isIncreasing = false;
    for (int i = res.digits.size() - 1; i >= 0; --i) {
        if (diff >= 0 && n1_ptr >= this->digits.begin()) {
            res.digits[i] += *n1_ptr;
            --n1_ptr;
            if (diff != 0) {
                isIncreasing = true;
            }
        }
        if (diff <= 0 && n2_ptr >= n.digits.begin()) {
            res.digits[i] += *n2_ptr;
            --n2_ptr;
        }

        if (diff != 0) {
            diff += isIncreasing ? -1 : 1;
        }
        if (res.digits[i] >= BASE) {
            res.digits[i] -= BASE;
            if (i == 0) {
                res.digits.emplace_front(1);
                res.expPos++;
                break;
            }
            res.digits[i - 1]++;
        }
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
    res.digits.resize(std::max(this->digits.size(), n.digits.size()));
    res.expPos = std::max(this->expPos, n.expPos);
    auto n1_ptr =
            this->digits.end() - 1; // std::deque<long long>::reverse_iterator
    auto n2_ptr = n.digits.end() - 1;
    long diff = this->digits.size() - this->expPos - n.digits.size() + n.expPos;
    bool isIncreasing = false;
    for (int i = res.digits.size() - 1; i >= 0; --i) {
        if (diff >= 0 && n1_ptr >= this->digits.begin()) {
            res.digits[i] += *n1_ptr;
            --n1_ptr;
            if (diff != 0) {
                isIncreasing = true;
            }
        }
        if (diff <= 0 && n2_ptr >= n.digits.begin()) {
            res.digits[i] -= *n2_ptr;
            --n2_ptr;
        }

        if (diff != 0) {
            diff += isIncreasing ? -1 : 1;
        }
        if (res.digits[i] < 0) {
            res.digits[i] += BASE;
            if (i == 0) {
                res.isNegative = !res.isNegative;
                res.digits.emplace_front(1);
                res.expPos++;
                break;
            }
            res.digits[i - 1]--;
        }
    }
    return res;
}

LongNum LongNum::operator*(const LongNum &n) const {
    LongNum res;
    bool popFirst = true;
    res.isNegative = (n.isNegative + this->isNegative) % 2;
    const std::deque<long long> number_1 = this->digits, number_2 = n.digits;
    std::deque<long long> res_number(number_1.size() + number_2.size() + 1);
    for (int i = static_cast<int>(number_1.size()) - 1; i >= 0; --i) {
        int carry = 0;
        for (int j = static_cast<int>(number_2.size()) - 1; j >= 0 || carry != 0;
             --j) {
            if (j == -1) {
                popFirst = false;
            }
            long long cur = res_number[i + j + 2] +
                            number_1[i] * (j >= 0 ? number_2[j] : 0) + carry;
            res_number[i + j + 2] = cur % BASE;
            carry = static_cast<int>(cur / BASE);
        }
    }
    res.expPos = this->expPos + n.expPos;
    if (popFirst) {
        res_number.pop_front();
    }
    if (*res_number.begin() == 0) {
        res_number.pop_front();
        res.expPos--;

    }
    int i = res_number.size() - 1;
    while (i >= res.expPos && res_number[i] == 0) {
        res_number.pop_back();
        i--;
    }

    res.digits = res_number;

    return res;
}

bool LongNum::operator!=(const LongNum &n) const {
    if (*this == n) {
        return false;
    }
    return true;
}

LongNum LongNum::inverse_number(int accuracy) const {
    LongNum n = 1.0_bigF;
    const LongNum mult = 10.0_bigF;
    std::string res = "";
    bool decrease_accuracy = false;
    while (accuracy > 0) {
        if (n == 0.0_bigF) {
            break;
        }
        int m = 0;
        LongNum l = 0.0_bigF;
        while (m + 1 < 10 && l + *this <= n) {
            l = l + *this;
            m++;
        }
        if (decrease_accuracy) {
            accuracy--;
        }
        res += std::to_string(m);
        if (n < *this) {
            res += ".";
            decrease_accuracy = true;
        }
        n = n - l;
        n = n * mult;
    }
    while (accuracy > 0) {
        res += "0";
        accuracy--;
    }
    LongNum inversed_number(res);
    return inversed_number;
}

LongNum LongNum::operator/(const LongNum &n) const {
    LongNum res = *this * n.inverse_number(200);
    return res;
}

std::string LongNum::toStr() const {
    std::string result;
    if (isNegative) {
        result += '-';
    }
    for (int i = 0; i < digits.size(); ++i) {
        if (i == expPos) {
            result += '.';
        }
        if (i == digits.size() - 1 && expPos != i + 1) {
            long long f = digits[i];
            while (f % 10 == 0) {
                f /= 10;
            }
            result += std::to_string(f);
        } else {
            result += std::to_string(digits[i]);
        }
    }
    return result;
}

std::ostream &operator<<(std::ostream &out, const LongNum &n) {
    out << n.toStr();
    return out;
}

LongNum operator ""_bigF(const char *x) { return {std::string{x}}; }
