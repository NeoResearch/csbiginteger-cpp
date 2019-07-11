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

namespace csBigInteger {
class BigInteger
{
private:
   // internal data (vector of bytes) in big-endian format (for readability)
   // efficiency is not important at this moment, correctness and portability is!
   vbyte _data;

public:
   // object accessible helper method
   // hex string is returned on little-endian
   std::string toHexStr() const
   {
      vbyte data = this->_data;               //this->ToByteArray();        // big-endian
      std::reverse(data.begin(), data.end()); // to little-endian
      std::string s = Helper::toHexString(data);
      // TODO: why not just return 's' here? some strange dependency exists between ToByteArray method...
      return s.length() == 0 ? "00" : s;
   }

public:
   const static BigInteger getMin; // get?
   const static BigInteger One;
   const static BigInteger Zero;
   const static BigInteger MinusOne;

   BigInteger(); // zero

   // default is base 10
   // allowed base 2
   // if base 16, prefix '0x' indicates big-endian, otherwise is little-endian
   BigInteger(std::string str, int base = 10);

   BigInteger(int32 value);
   BigInteger(int64 value);
   BigInteger(const BigInteger& value);

   // byte data in little-endian format
   BigInteger(vbyte data);

   bool operator==(const BigInteger& big);
   bool operator!=(const BigInteger& big);

   bool operator<=(const BigInteger& big);
   bool operator<(const BigInteger& big);

   bool operator>=(const BigInteger& big);
   bool operator>(const BigInteger& big);

   bool IsZero() const;

   // this one is little-endian
   vbyte ToByteArray() const
   {
      if (this->_data.size() == 0)
         return vbyte(1, 0x00);
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

      std::cout << "NOT IMPLEMENTED ToString() for base = " << base << std::endl;
      exit(1);

      return "";
   }

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

   BigInteger operator+(BigInteger& big2);
   BigInteger operator+(long l2);

   BigInteger& operator+=(int i2);

   BigInteger operator-(BigInteger& big2);

   BigInteger& operator-=(int i2);

   // negate (unary)
   BigInteger operator-();

   BigInteger operator*(BigInteger& big2);
   BigInteger operator*(long l2);

   BigInteger operator/(BigInteger& big2);

   BigInteger operator%(BigInteger& big2);

   BigInteger& operator<<=(int i2);

   BigInteger& operator>>=(int i2);

   // what is needed here?
};
}

#endif // CS_BIGINTEGER_BIGINTEGER_H
