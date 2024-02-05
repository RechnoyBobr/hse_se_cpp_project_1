#pragma once

#include <deque>
#include <string>

class LongNum {
  std::deque<long long> digits;
  long exp;
  long expPos;
  // numbers closer to the beginning is less than the ones that closer to end
  // f_part[0] < f_part[1]
  const long long BASE = 1000000;
  bool isNegative;

public:
  LongNum();

  LongNum(const std::string &num); // NOLINT(*-explicit-constructor)

  void inverse_sign();

  [[nodiscard]] std::string toStr() const; // Returns number as string

  LongNum operator+(const LongNum &n) const;

  LongNum operator*(const LongNum &n) const;

  LongNum operator-(const LongNum &n) const;

  LongNum operator-();
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
};

LongNum operator""_bigF(const char *x);
