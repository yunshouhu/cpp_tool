#ifndef CBIGINT_H
#define CBIGINT_H

#include "CStrUtil.h"
#include <iostream>
#include <algorithm>

//https://github.com/colinw7/CBigInt
class CBigInt {
 public:
  CBigInt(long value=0) {
    init(value);
  }

  CBigInt(const std::string &str) {
    init(str);
  }

  CBigInt(const char *str) {
    init(str);
  }

  CBigInt(const CBigInt &a) :
   is_nan_(a.is_nan_), is_negative_(a.is_negative_), is_value_(a.is_value_),
   value_(a.value_), str_(a.str_) {
  }

  friend CBigInt operator+(const CBigInt &a, const CBigInt &b);
  friend CBigInt operator-(const CBigInt &a, const CBigInt &b);
  friend CBigInt operator*(const CBigInt &a, const CBigInt &b);
  friend CBigInt operator/(const CBigInt &a, const CBigInt &b);
  friend CBigInt operator%(const CBigInt &a, const CBigInt &b);

  friend bool operator< (const CBigInt &a, const CBigInt &b);
  friend bool operator> (const CBigInt &a, const CBigInt &b);
  friend bool operator<=(const CBigInt &a, const CBigInt &b);
  friend bool operator>=(const CBigInt &a, const CBigInt &b);
  friend bool operator==(const CBigInt &a, const CBigInt &b);
  friend bool operator!=(const CBigInt &a, const CBigInt &b);

  friend CBigInt &operator+=(CBigInt &a, const CBigInt &b) {
    a = a + b;

    return a;
  }

  friend CBigInt &operator-=(CBigInt &a, const CBigInt &b) {
    a = a - b;

    return a;
  }

  friend CBigInt &operator*=(CBigInt &a, const CBigInt &b) {
    a = a * b;

    return a;
  }

  friend CBigInt &operator/=(CBigInt &a, const CBigInt &b) {
    a = a / b;

    return a;
  }

  friend CBigInt &operator%=(CBigInt &a, const CBigInt &b) {
    a = a % b;

    return a;
  }

  const CBigInt operator-() const {
    if (isNaN())
      return *this;

    CBigInt b = *this;

    b.negate();

    return b;
  }

  const CBigInt operator+() const {
    return *this;
  }

  CBigInt &operator=(const CBigInt &b) {
    if (this == &b)
      return *this;

    is_nan_      = b.is_nan_;
    is_negative_ = b.is_negative_;
    is_value_    = b.is_value_;
    value_       = b.value_;
    str_         = b.str_;

    return *this;
  }

  const CBigInt operator++() {
    if (isNaN())
      return *this;

    *this = *this + 1;

    return *this;
  }

  const CBigInt operator++(int) {
    if (isNaN())
      return *this;

    CBigInt t = *this;

    *this = *this + 1;

    return t;
  }

  const CBigInt operator--() {
    if (isNaN())
      return *this;

    *this = *this - 1;

    return *this;
  }

  const CBigInt operator--(int) {
    if (isNaN())
      return *this;

    CBigInt t = *this;

    *this = *this - 1;

    return t;
  }

  CBigInt power(const CBigInt &b) const;

  CBigInt factorial() const;

  bool isZero() const {
    if (isNaN())
      return false;

    if (is_value_)
      return (value_ == 0);
    else
      return (str_ == "0");
  }

  bool isOne() const {
    if (isNaN())
      return false;

    if (is_value_)
      return (value_ == 1);
    else
      return (str_ == "1");
  }

  bool isOdd() const {
    if (isNaN())
      return true;

    if (is_value_)
      return (value_ & 1);
    else
      return (str_[0] == '1' || str_[0] == '3' ||
              str_[0] == '5' || str_[0] == '7' || str_[0] == '9');
  }

  bool isEven() const {
    return ! isOdd();
  }

  void negate() {
    is_negative_ = ! is_negative_;
  }

  bool isNegative() const {
    if (isNaN())
      return false;

    return is_negative_;
  }

  bool isPositive() const {
    return ! isNegative();
  }

  bool isNaN() const {
    return is_nan_;
  }

  void setNaN() {
    is_nan_ = true;
  }

  static CBigInt NaN() {
    CBigInt nan;

    nan.setNaN();

    return nan;
  }

  void print(std::ostream &os = std::cout) const {
    os << toString();
  }

  friend std::ostream &operator<<(std::ostream &os, const CBigInt &i) {
    i.print(os);

    return os;
  }

  std::string toString() const {
    if (isNaN())
      return "NaN";

    std::string str;

    if (isNegative())
      str += "-";

    if (is_value_)
      str += CStrUtil::toString(value_);
    else
      str += '\"' + str_ + '\"';

    return str;
  }

 private:
  void init(long value) {
    is_nan_   = false;
    is_value_ = true;

    if (value < 0) {
      is_negative_ = true;
      value_       = -value;
    }
    else {
      is_negative_ = false;
      value_       = value;
    }
  }

  void init(const std::string &str) {
    is_nan_      = false;
    is_negative_ = false;
    is_value_    = false;

    uint len = str.size();

    if (len < 1) {
     // CTHROW("Invalid Integer");
      is_value_  = true;
      value_     = 0;
      return;
    }

    if (CStrUtil::casecmp(str, "nan") == 0) {
      is_nan_ = true;
      return;
    }

    uint start = 0;

    if (str[start] == '-') {
      is_negative_ = true;

      if (len < 2) {
       // CTHROW("Invalid Integer");
        is_value_ = true;
        value_    = 0;
        return;
      }

      start++;
    }

    for (uint i = start; i < len; i++) {
      if (! isdigit(str[i])) {
       // CTHROW("Invalid Integer");
        is_value_ = true;
        value_    = 0;
        return;
      }
    }

    str_ = str.substr(start);

    stripLeadingZeros();

    if (isZero())
      is_negative_ = false;

    if (CStrUtil::isInteger(str_)) {
      long value1;

      is_value_ = true;

      CStrUtil::toInteger(str_, &value1);

      value_ = value1;
    }
  }

  CBigInt &convString() {
    if (! is_value_)
      return *this;

    is_value_ = false;

    str_ = CStrUtil::toString(value_);

    return *this;
  }

  CBigInt multiplyByDigit(int multiplier) const;

  void setDigit(int digit, int pos) {
    char c = (digit + '0');

    while (pos >= (int) str_.size())
      str_ = "0" + str_;

    str_[str_.size() - pos - 1] = c;
  }

  int getDigit(int pos) const {
    if (pos < 0 || pos >= (int) str_.size())
      return 0;

    return (int) (str_[str_.size() - pos - 1] - '0');
  }

  int getRDigit(int pos) const {
    if (pos < 0 || pos >= (int) str_.size())
      return 0;

    return (int) (str_[pos] - '0');
  }

  void shiftLeft(int num) {
    for (int i = 0; i < num; i++)
      str_ += "0";
  }

  void stripLeadingZeros() {
    while (str_.size() > 1 && str_[0] == '0') {
      str_ = str_.substr(1);
    }
  }

 private:
  bool        is_nan_ { false };
  bool        is_negative_ { false };
  bool        is_value_ { false };
  ulong       value_ { 0 };
  std::string str_;
};

namespace CBigIntC {
  static CBigInt Zero { 0L };
  static CBigInt One  { 1L };
}

#endif
