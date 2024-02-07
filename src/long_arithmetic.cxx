#include "../include/long_arithmetic.h"
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
    int i = 0;
    while (i != this->digits.size()) {
        if (this->digits[i] != 0) {
            this->isNegative = !this->isNegative;
            return *this;
        }
        i++;
    }
    return *this;
}

LongNum::LongNum(const std::string &num) {
    int i = 0;
    isNegative = false; // _bigF operator don't recognize - as a char, but as a
    // unary operator.
    while (i < num.size() && num[i] != '.') {
        i++;
    }
    expPos = i / BASE_SIZE + (i % BASE_SIZE ? 1 : 0);
    digits.resize(i / BASE_SIZE + (i % BASE_SIZE ? 1 : 0));
    auto int_end = digits.end(); // std::deque<long long>:iterator;
    int block = i - 1;
    while (int_end != digits.begin()) {
        --int_end;
        int to = block - 8;
        long long n = 0, mp = 1;
        for (; block >= std::max(to, 0); block--) {
            n += (num[block] - '0') * mp;
            mp *= 10;
        }
        *int_end = n;
        to = block - 1;
    }
    digits.resize(digits.size() + (num.size() - i - 1) / BASE_SIZE +
                  ((num.size() - i - 1) % BASE_SIZE ? 1 : 0));
    block = i + 1;
    auto frac = digits.begin() + i / BASE_SIZE + (i % BASE_SIZE ? 1 : 0);
    while (frac != digits.end()) {
        int to = block + 8, n = 0, cnt = 0;
        for (; block <= std::min(to, static_cast<int>(num.size()) - 1); ++block) {
            n *= 10;
            n += num[block] - '0';
            cnt++;
        }
        if (block == num.size() && n != 0) {
            while (cnt < BASE_SIZE) {
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
    if (this->isNegative && !n.isNegative) {
        return true;
    }
    if (!this->isNegative && n.isNegative) {
        return false;
    }
    if (this->isNegative && n.isNegative) {
        if (this->expPos > n.expPos) {
            return false;
        }
        if (this->expPos < n.expPos) {
            return true;
        }
        for (int i = 0; i < std::min(this->digits.size(), n.digits.size()); i++) {
            if (this->digits[i] > n.digits[i]) {
                return false;
            }
            if (this->digits[i] < n.digits[i]) {
                return true;
            }
        }
        if (digits.size() > n.digits.size()) {
            for (int i = static_cast<int>(n.digits.size()); i < digits.size(); ++i) {
                if (digits[i] != 0) {
                    return false;
                }
            }
        } else if (digits.size() > n.digits.size()) {
            for (int i = static_cast<int>(digits.size()); i < n.digits.size(); ++i) {
                if (n.digits[i] != 0) {
                    return true;
                }
            }
        }
        return false;
    }
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
    if (this->isNegative && !n.isNegative) {
        return true;
    }
    if (!this->isNegative && n.isNegative) {
        return false;
    }
    if (this->isNegative && n.isNegative) {
        if (this->expPos < n.expPos) {
            return false;
        }
        if (this->expPos > n.expPos) {
            return true;
        }
        for (int i = 0; i < std::min(this->digits.size(), n.digits.size()); i++) {
            if (this->digits[i] < n.digits[i]) {
                return false;
            }
            if (this->digits[i] > n.digits[i]) {
                return true;
            }
        }
        if (digits.size() > n.digits.size()) {
            for (int i = n.digits.size(); i < digits.size(); ++i) {
                if (digits[i] != 0) {
                    return true;
                }
            }
        } else if (digits.size() > n.digits.size()) {
            for (int i = digits.size(); i < n.digits.size(); ++i) {
                if (n.digits[i] != 0) {
                    return false;
                }
            }
        }
        return false;
    }
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
    this->expPos = n.expPos;
    return *this;
}

LongNum LongNum::operator+(const LongNum &n) const {
    if (*this == 0.0_bigF) {
        return n;
    }
    if (n == 0.0_bigF) {
        return *this;
    }
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
    res.digits.resize(std::max(expPos, n.expPos) + std::max(digits.size() - expPos, n.digits.size() - n.expPos));
    res.expPos = std::max(this->expPos, n.expPos);
    auto n1_ptr =
            this->digits.end() - 1; // std::deque<long long>::iterator
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
    while (res.digits[0] == 0 && res.expPos > 1) {
        res.digits.pop_front();
        res.expPos--;
    }
    return res;
}

LongNum LongNum::operator*(const LongNum &n) const {
    if (*this == 0.0_bigF || n == 0.0_bigF) {
        return 0.0_bigF;
    }
    LongNum res;
    bool popFirst = true;
    int sz_this = std::to_string(digits[0]).size();
    int sz_n = std::to_string(n.digits[0]).size();
    res.expPos =
            this->expPos - 1 + n.expPos - 1 + (sz_this + sz_n) / BASE_SIZE + ((sz_this + sz_n) % BASE_SIZE ? 1 : 0);
    res.isNegative = (n.isNegative + this->isNegative) % 2;
    const std::deque<long long> number_1 = this->digits, number_2 = n.digits;
    std::deque<long long> res_number(res.expPos + (number_1.size() + number_2.size() - expPos - n.expPos) + 1);
    for (int i = static_cast<int>(number_1.size()) - 1; i >= 0; --i) {
        int carry = 0;
        for (int j = static_cast<int>(number_2.size()) - 1; j >= 0 || carry != 0;
             --j) {
            if (i + j + 1 == 0) {
                popFirst = false;
            }
            long long cur = res_number[i + j + 1] +
                            number_1[i] * (j >= 0 ? number_2[j] : 0) + carry;
            res_number[i + j + 1] = cur % BASE;
            carry = static_cast<int>(cur / BASE);
        }
    }
    if (popFirst) {
        res_number.pop_front();
    }
    int i = res_number.size() - 1;
    while (i > res.expPos && res_number[i] == 0) {
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
    const LongNum mult = 10.0_bigF;
    LongNum n = 1.0_bigF, n1 = *this;
    n1.isNegative = false;
    n.isNegative = false;

    accuracy = std::max(accuracy, 300);
    std::string res = "";
    bool decrease_accuracy = false;
    while (accuracy > 0) {
        if (n == 0.0_bigF) {
            break;
        }
        if (n < n1 && !decrease_accuracy) {
            if (res.size() == 0) {
                res = "0";
            }
            res += ".";
            decrease_accuracy = true;
        }
        if (decrease_accuracy) {
            n = n * mult;
        }
        int m = 0;
        LongNum l = 0.0_bigF;
        while (m + 1 < 10 && l + n1 <= n) {
            l = l + n1;
            m++;
        }
        if (decrease_accuracy) {
            accuracy--;
        }
        res += std::to_string(m);
        n = n - l;
        if (n.digits[0] == 0) {
            n.digits.pop_front();
            n.expPos--;
        }
    }
    while (accuracy > 0) {
        res += "0";
        accuracy--;
    }
    LongNum inverse_number(res);
    return inverse_number;
}

LongNum LongNum::operator/(const LongNum &number) const {
    if (*this == 0.0_bigF) {
        return 0.0_bigF;
    }
    const LongNum mult = 10.0_bigF;
    LongNum n = *this, n1 = number;
    n1.isNegative = false;
    n.isNegative = false;
    int accuracy = static_cast<int>(std::max(n.digits.size() * BASE_SIZE, digits.size() * BASE_SIZE));
    accuracy = accuracy;
    std::string res = "";
    bool decrease_accuracy = false;
    while (accuracy > 0) {
        if (n == 0.0_bigF) {
            break;
        }
        if (n < n1 && !decrease_accuracy) {
            if (res.size() == 0) {
                res = "0";
            }
            res += ".";
            decrease_accuracy = true;
        }
        if (decrease_accuracy) {
            n = n * mult;
        }
        int m = 0;
        LongNum l = 0.0_bigF;
        while (m + 1 < 10 && l + n1 <= n) {
            l = l + n1;
            m++;
        }
        if (decrease_accuracy) {
            accuracy--;
        }
        res += std::to_string(m);
        n = n - l;
        if (n < n1 && !decrease_accuracy) {
            if (res.size() == 0) {
                res = "0";
            }
            res += ".";
            decrease_accuracy = true;
        }

    }
    while (accuracy > 0) {
        res += "0";
        accuracy--;
    }
    LongNum inverse_number(res);
    return inverse_number;
}

// TODO: pi/4 = arctg1/2 + arctg1/3
// arctg x = x - x^3/3 +x^5/5 -x^7/7 + x^9/9 +....
// TODO: what is the n to make pi with accuracy of 4.

std::string LongNum::toStr() const {
    std::string result;
    if (isNegative) {
        result += '-';
    }
    for (int i = 0; i < digits.size(); ++i) {
        if (i == expPos) {
            result += '.';
        }
        if (i >= expPos && (i != digits.size() - 1 || i == expPos)) {
            int sz = std::to_string(digits[i]).size();
            for (int j = BASE_SIZE - sz; j > 0; --j) {
                result += "0";
            }
        }
        if (i == digits.size() - 1 && expPos != i + 1) {
            long long f = digits[i];
            while (f % 10 == 0 && f != 0) {
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

void LongNum::operator+=(const LongNum &n) {
    *this = *this + n;
}

void LongNum::operator-=(const LongNum &n) {
    *this = *this - n;
}

void LongNum::strip(int n) {
    int size = this->expPos + n / BASE_SIZE + 1 + (n % BASE_SIZE ? 1 : 0);
    int to = n % BASE_SIZE;
    digits.resize(size);
    digits[size - 1] =
            (digits.size() / static_cast<long long>(pow(10, BASE_SIZE - to))) *
            static_cast<long long>(pow(10, BASE_SIZE - to));
    while (digits.size() > expPos && *(digits.end() - 1) == 0) {
        digits.pop_back();
    }
}

LongNum pie(int accuracy) {
    int iters = accuracy - 20;
    clock_t t_1 = clock();
    LongNum p = 0.0_bigF, n1 = 0.2_bigF, n2 = (239.0_bigF).inverse_number(accuracy), d = 1.0_bigF;
    LongNum mult1 = n1 * n1, mult2 = n2 * n2, four = 4.0_bigF, x, x1, x2;
    for (int i = 0; i < iters; ++i) {
        x = four * n1;
        x1 = x - n2;
        x2 = x1 / d;
        //std::cout << p << " " << x << " " << x1 << " " << x2 << "\n";
        if (i % 2 == 0) {
            p += x2;
        } else {
            p -= x2;
        }
        p.strip(accuracy+150);
        n1 = n1 * mult1;
        n2 = n2 * mult2;
        n1.strip(accuracy+150);
        n2.strip(accuracy+150);

        d += 2.0_bigF;

    }
    // At this moment it returns pi/4, so we have to multiply by four
    p = p * four;
    clock_t t_2 = clock();
    std::cout << "Time used to calculate pi: " << 1000 * (t_2 - t_1) / CLOCKS_PER_SEC << "ms\n";
    p.strip(accuracy);
    return p;
}
