#ifndef CS_BIGINTEGER_BIGINTEGER_H
#define CS_BIGINTEGER_BIGINTEGER_H

// system includes
#include <algorithm>
#include <iomanip>
#include <iostream> // todo: remove
#include <sstream>
#include <vector>

// internal classes
#include "Helper.hpp"

// original specification:
// https://referencesource.microsoft.com/#System.Numerics/System/Numerics/BigInteger.cs

// ======================================
// This class is intended to be immutable
// ======================================

namespace csbiginteger {
class BigInteger final
{
private:
   // internal data (vector of bytes) in big-endian format (for readability)
   // efficiency is not important at this moment, correctness and portability is!
   // TODO: perhaps it's better to store in little-endian format... see which methods are affected.
   vbyte _data;

public:
   // size in bytes
   int Length() const
   {
      return _data.size();
   }

   // copy internal bytes (in little-endian) to external array vr. returns 'true' if ok, 'false' if problems.
   bool CopyTo(byte* vr, int sz_vr) const
   {
      // check if size is enough
      if (sz_vr < Length())
         return false;
      vbyte data = _data;                     // big-endian
      std::reverse(data.begin(), data.end()); // to little-endian
      std::copy(data.begin(), data.end(), vr);
      return true;
   }

   const static BigInteger getMin; // get?
   const static BigInteger One;
   const static BigInteger Zero;
   const static BigInteger MinusOne;

public:
   // zero
   BigInteger();

   // copy constructor
   BigInteger(const BigInteger& value);

   // move constructor
   BigInteger(BigInteger&& corpse);

   // destructor
   //virtual ~BigInteger();

   // default is base 10
   // allowed base 2
   // if base 16, prefix '0x' indicates big-endian, otherwise is little-endian
   BigInteger(std::string str, int base = 10);

   BigInteger(int32 value);
   BigInteger(int64 value);
   // from single-precision
   BigInteger(float f);

   // byte data in little-endian format
   BigInteger(vbyte data);

   // BigInteger is the same when _data is the same
   // _data must be always in its most compressed format (except by zero)
   bool operator==(const BigInteger& big) const
   {
      return this->_data == big._data;
   }

   bool operator!=(const BigInteger& big) const
   {
      return !((*this) == big);
   }

   // depends on external implementation
   bool operator<(const BigInteger& big) const;
   bool operator<=(const BigInteger& big) const
   {
      return ((*this) == big) || ((*this) < big); // where is spaceship operator??
   }

   // depends on external implementation
   bool operator>(const BigInteger& big) const;
   bool operator>=(const BigInteger& big) const
   {
      return ((*this) == big) || ((*this) > big); // where is spaceship operator??
   }

   bool IsZero() const
   {
      return (*this) == Zero;
   }

   // TODO: expose or not to expose this? make it private?
   bool IsError() const
   {
      return (*this) == Error;
   }

   // this one is little-endian
   vbyte ToByteArray() const
   {
      vbyte data = this->_data; // copy
      std::reverse(data.begin(), data.end());
      return std::move(data); // move
   }

   // this one is big-endian (prefixed 0x, to enforce hex format)
   std::string ToString(int base = 16) const
   {
      if (base == 16) {
         std::stringstream ss;
         ss << "0x" << Helper::revertHexString(this->toHexStr()); // to big-endian
         return ss.str();
      }

      if (base == 2) {
         std::stringstream ss;
         for (unsigned i = 0; i < _data.size(); i++)
            ss << Helper::parseBin(_data[i]); // byte to binary (TODO: verify if size is 8)
         return ss.str();
      }

      // base 10
      return toStringBase10();
   }

private:
   std::string toStringBase10() const;

public:
   // native int32 format
   int32 toInt() const;

   // native int64 format
   int64 toLong() const;

   int Sign() const;

   static BigInteger Abs(const BigInteger& big);

   static BigInteger Min(const BigInteger& big1, const BigInteger& big2);

   static BigInteger Max(const BigInteger& big1, const BigInteger& big2);

   // operators

   // ~ is the unary one's complement operator -- it flips the bits of its operand.
   BigInteger operator~();

   BigInteger operator&(BigInteger& big2);

   BigInteger operator|(BigInteger& big2);

   BigInteger operator^(BigInteger& big2);

   // depends on external implementation
   BigInteger operator+(const BigInteger& big2) const;
   BigInteger operator+(long l2) const
   {
      BigInteger other(l2);
      return (*this) + other;
   }

   // immutable??
   BigInteger& operator+=(int i2);

   // depends on external implementation
   BigInteger operator-(const BigInteger& big2) const;
   BigInteger operator-(long l2) const
   {
      BigInteger other(l2);
      return (*this) - other;
   }

   // immutable ??
   BigInteger& operator-=(int i2);

   // negate (unary)
   BigInteger operator-() const
   {
      return BigInteger::Zero - (*this);
   }

   // depends on external implementation
   BigInteger operator*(const BigInteger& big2) const;
   BigInteger operator*(long l2) const
   {
      BigInteger other(l2);
      return (*this) * other;
   }

   // depends on external implementation
   BigInteger operator/(const BigInteger& big2) const;
   BigInteger operator/(long l2) const
   {
      BigInteger other(l2);
      return (*this) / other;
   }

   // depends on external implementation
   BigInteger operator%(const BigInteger& big2) const;
   BigInteger operator%(long l2) const
   {
      BigInteger other(l2);
      return (*this) / other;
   }

   // immutable??
   BigInteger& operator<<=(int i2);

   // depends on external implementation
   BigInteger operator<<(const BigInteger& big2) const;
   BigInteger operator<<(long l2) const
   {
      BigInteger other(l2);
      return (*this) << other;
   }

   // immutable??
   BigInteger& operator>>=(int i2);

   // depends on external implementation
   BigInteger operator>>(const BigInteger& big2) const;
   BigInteger operator>>(long l2) const
   {
      BigInteger other(l2);
      return (*this) >> other;
   }

   // what else is needed here?

   // Utils

   // pow allows int32 positive exponent (negative will generate BigInteger::Error)
   static BigInteger Pow(BigInteger value, int exponent);
   static BigInteger Multiply(BigInteger value1, BigInteger value2)
   {
      return value1 * value2;
   }

public:
   // object accessible helper method
   // hex string is returned on little-endian
   std::string toHexStr() const
   {
      vbyte data = this->ToByteArray(); // little-endian
      std::string s = Helper::toHexString(data);
      return s;
   }

private:
   const static BigInteger error();

public:
   const static BigInteger Error; // error biginteger (empty internal bytearray)
};
}

#endif // CS_BIGINTEGER_BIGINTEGER_H
