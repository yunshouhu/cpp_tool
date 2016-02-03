#include "CBigInt.h"

CBigInt
operator+(const CBigInt &a, const CBigInt &b)
{
  if (a.isNaN() ||  b.isNaN())
    return CBigInt::NaN();

  if (a.isNegative() || b.isNegative()) {
    if      (! a.isNegative())
      return  (  a  - (-b));
    else if (! b.isNegative())
      return -((-a) -   b );
    else
      return -((-a) + (-b));
  }

  if (a.is_value_ || b.is_value_) {
    if      (! a.is_value_) {
      CBigInt b1 = b;

      return a + b1.convString();
    }
    else if (! b.is_value_) {
      CBigInt a1 = a;

      return a1.convString() + b;
    }
    else {
      ulong value1 = a.value_ + b.value_;

      if (value1 < std::max(a.value_, b.value_) || ((long) value1) < 0) {
        CBigInt a1 = a;
        CBigInt b1 = b;

        return a1.convString() + b1.convString();
      }

      return CBigInt(value1);
    }
  }

  CBigInt c;

  c.str_      = "0";
  c.is_value_ = false;

  int size1 = a.str_.size();
  int size2 = b.str_.size();

  int max_size = (size1 > size2 ? size1 : size2);

  int carry = 0;

  int pos = 0;

  for (int i = 0; i < max_size; i++) {
    int sum = a.getDigit(i) + b.getDigit(i) + carry;

    c.setDigit(sum % 10, pos++);

    carry = (sum >= 10);
  }

  if (carry > 0)
    c.setDigit(carry, pos);

  return c;
}

CBigInt
operator-(const CBigInt &a, const CBigInt &b)
{
  if (a.isNaN() ||  b.isNaN())
    return CBigInt::NaN();

  if (a.isNegative() || b.isNegative()) {
    if      (! a.isNegative())
      return  (  a  + (-b));
    else if (! b.isNegative())
      return -((-a) +   b );
    else
      return -((-a) - (-b));
  }

  if (a < b)
    return -(b - a);

  if (a.is_value_ || b.is_value_) {
    if      (! a.is_value_) {
      CBigInt b1 = b;

      return a - b1.convString();
    }
    else if (! b.is_value_) {
      CBigInt a1 = a;

      return a1.convString() - b;
    }
    else {
      ulong value1 = a.value_ - b.value_;

      if (value1 > std::max(a.value_, b.value_) || ((long) value1) < 0) {
        CBigInt a1 = a;
        CBigInt b1 = b;

        return a1.convString() - b1.convString();
      }

      return CBigInt(value1);
    }
  }

  CBigInt c;

  c.str_      = "0";
  c.is_value_ = false;

  int size1 = a.str_.size();

  int carry = 0;

  int pos = 0;

  int i = 0;

  while (i < size1) {
    int diff = a.getDigit(i) - b.getDigit(i) + carry;

    if (diff < 0) {
      carry = -1;

      diff += 10;
    }

    c.setDigit(diff % 10, pos++);

    i++;
  }

  c.stripLeadingZeros();

  return c;
}

CBigInt
operator*(const CBigInt &a, const CBigInt &b)
{
  if (a.isNaN() ||  b.isNaN())
    return CBigInt::NaN();

  if (a.isNegative() || b.isNegative()) {
    if      (! a.isNegative())
      return -(  a  * (-b));
    else if (! b.isNegative())
      return -((-a) *   b );
    else
      return  ((-a) * (-b));
  }

  if (a.is_value_ || b.is_value_) {
    if      (! a.is_value_) {
      CBigInt b1 = b;

      return a * b1.convString();
    }
    else if (! b.is_value_) {
      CBigInt a1 = a;

      return a1.convString() * b;
    }
    else {
      ulong value1 = a.value_ * b.value_;

      if (value1 < std::max(a.value_, b.value_) || ((long) value1) < 0) {
        CBigInt a1 = a;
        CBigInt b1 = b;

        return a1.convString() * b1.convString();
      }

      return CBigInt(value1);
    }
  }

  CBigInt c;

  int size2 = b.str_.size();

  for (int i = 0; i < size2; i++) {
    CBigInt c1 = a.multiplyByDigit(b.getDigit(i));

    c1.shiftLeft(i);

    c += c1;
  }

  return c;
}

CBigInt
CBigInt::
multiplyByDigit(int multiplier) const
{
  int size = str_.size();

  CBigInt c;

  c.str_      = "0";
  c.is_value_ = false;

  int carry = 0;

  int pos = 0;

  for (int i = 0; i < size; i++) {
    int product = getDigit(i)*multiplier + carry;

    carry = product / 10;

    c.setDigit(product % 10, pos++);
  }

  if (carry > 0)
    c.setDigit(carry, pos);

  return c;
}

CBigInt
operator/(const CBigInt &a, const CBigInt &b)
{
  if (a.isNaN() ||  b.isNaN())
    return CBigInt::NaN();

  if (b.isZero())
    return CBigInt::NaN();

  if (a.isNegative() || b.isNegative()) {
    if      (! a.isNegative())
      return -(  a  / (-b));
    else if (! b.isNegative())
      return -((-a) /   b );
    else
      return  ((-a) / (-b));
  }

  if (b > a)
    return CBigInt(0L);

  if (a.is_value_ || b.is_value_) {
    if      (! a.is_value_) {
      CBigInt b1 = b;

      return a / b1.convString();
    }
    else if (! b.is_value_) {
      CBigInt a1 = a;

      return a1.convString() / b;
    }
    else {
      ulong value1 = a.value_ / b.value_;

      if (value1 > std::max(a.value_, b.value_) || ((long) value1) < 0) {
        CBigInt a1 = a;
        CBigInt b1 = b;

        return a1.convString() / b1.convString();
      }

      return CBigInt(value1);
    }
  }

  CBigInt c;

  c.str_      = "0";
  c.is_value_ = false;

  int cpos = 0;

  CBigInt d;

  int dpos = 0;

  int size = a.str_.size();

  for (int i = 0; i < size; i++) {
    if (dpos > 0)
      d.shiftLeft(1);

    d.setDigit(a.getRDigit(i), 0);

    dpos++;

    if (d < b)
      continue;

    int count = 0;

    while (d >= b) {
      d -= b;

      count++;
    }

    if (d.isZero())
      dpos = 0;

    if (cpos > 0)
      c.shiftLeft(1);

    c.setDigit(count, 0);

    cpos++;
  }

  return c;
}

CBigInt
operator%(const CBigInt &a, const CBigInt &b)
{
  if (a.isNaN() ||  b.isNaN())
    return CBigInt::NaN();

  if (b.isZero())
    return CBigInt::NaN();

  if (a.isNegative() || b.isNegative()) {
    if      (! a.isNegative())
      return   a  % (-b);
    else if (! b.isNegative())
      return (-a) %   b ;
    else
      return (-a) % (-b);
  }

  if (b > a)
    return a;

  if (a.is_value_ || b.is_value_) {
    if      (! a.is_value_) {
      CBigInt b1 = b;

      return a % b1.convString();
    }
    else if (! b.is_value_) {
      CBigInt a1 = a;

      return a1.convString() % b;
    }
    else {
      ulong value1 = a.value_ % b.value_;

      if (value1 > std::max(a.value_, b.value_) || ((long) value1) < 0) {
        CBigInt a1 = a;
        CBigInt b1 = b;

        return a1.convString() % b1.convString();
      }

      return CBigInt(value1);
    }
  }

  CBigInt c;

  int cpos = 0;

  int size = a.str_.size();

  for (int i = 0; i < size; i++) {
    if (cpos > 0)
      c.shiftLeft(1);

    c.setDigit(a.getRDigit(i), 0);

    cpos++;

    if (c < b)
      continue;

    int count = 0;

    while (c >= b) {
      c -= b;

      count++;
    }

    if (c.isZero())
      cpos = 0;
  }

  return c;
}

bool
operator<(const CBigInt &a, const CBigInt &b)
{
  if (a.isNaN() ||  b.isNaN()) {
    if      (! a.isNaN())
      return false;
    else if (! b.isNaN())
      return true;
    else
      return false;
  }

  if (a.isNegative() || b.isNegative()) {
    if      (! a.isNegative())
      return false;
    else if (! b.isNegative())
      return true;
    else
      return ((-a) > (-b));
  }

  if (a.is_value_ || b.is_value_) {
    if      (! a.is_value_) {
      CBigInt b1 = b;

      return a < b1.convString();
    }
    else if (! b.is_value_) {
      CBigInt a1 = a;

      return a1.convString() < b;
    }
    else
      return a.value_ < b.value_;
  }

  int size1 = a.str_.size();
  int size2 = b.str_.size();

  if (size1 != size2)
    return size1 < size2;

  return (a.str_ < b.str_);
}

bool
operator>(const CBigInt &a, const CBigInt &b)
{
  if (a.isNaN() ||  b.isNaN()) {
    if      (! a.isNaN())
      return true;
    else if (! b.isNaN())
      return false;
    else
      return false;
  }

  if (a.isNegative() || b.isNegative()) {
    if      (! a.isNegative())
      return true;
    else if (! b.isNegative())
      return false;
    else
      return ((-a) < (-b));
  }

  if (a.is_value_ || b.is_value_) {
    if      (! a.is_value_) {
      CBigInt b1 = b;

      return a > b1.convString();
    }
    else if (! b.is_value_) {
      CBigInt a1 = a;

      return a1.convString() > b;
    }
    else
      return a.value_ > b.value_;
  }

  int size1 = a.str_.size();
  int size2 = b.str_.size();

  if (size1 != size2)
    return size1 > size2;

  return (a.str_ > b.str_);
}

bool
operator<=(const CBigInt &a, const CBigInt &b)
{
  return ! (a > b);
}

bool
operator>=(const CBigInt &a, const CBigInt &b)
{
  return ! (a < b);
}

bool
operator==(const CBigInt &a, const CBigInt &b)
{
  if (a.isNaN() || b.isNaN())
    return a.isNaN() && b.isNaN();

  if (a.isZero() && b.isZero())
    return true;

  if (a.is_negative_ != b.is_negative_)
    return false;

  if (a.is_value_ || b.is_value_) {
    if      (! a.is_value_) {
      CBigInt b1 = b;

      return a == b1.convString();
    }
    else if (! b.is_value_) {
      CBigInt a1 = a;

      return a1.convString() == b;
    }
    else
      return a.value_ == b.value_;
  }

  int size1 = a.str_.size();
  int size2 = b.str_.size();

  if (size1 != size2)
    return false;

  return (a.str_ == b.str_);
}

bool
operator!=(const CBigInt &a, const CBigInt &b)
{
  return ! (a == b);
}

CBigInt
CBigInt::
power(const CBigInt &b) const
{
  if (isNaN() ||  b.isNaN())
    return CBigInt::NaN();

  CBigInt c;

  CBigInt i;

  c = 1;

  while (i < b) {
    c = c*(*this);

    i++;
  }

  return c;
}

CBigInt
CBigInt::
factorial() const
{
  if (isNaN())
    return CBigInt::NaN();

  if (*this < 0L)
    return CBigInt::NaN();

  if (*this == 0L || *this == 1L)
    return *this;

  CBigInt a = *this - 1L;

  return (*this)*a.factorial();
}
