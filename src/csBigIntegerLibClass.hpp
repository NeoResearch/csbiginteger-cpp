#ifndef CSBIGINTEGERLIB_BIGINTEGER_HPP
#define CSBIGINTEGERLIB_BIGINTEGER_HPP

// system includes
#include <algorithm>
#include <iomanip>
#include <iostream> // todo: remove
#include <sstream>
#include <vector>

#include "csBigIntegerLib.h" // NEVER INCLUDE "BigInteger.h" HERE!

// internal classes
#include "Helper.hpp" // from namespace 'csbiginteger'

// original specification:
// https://referencesource.microsoft.com/#System.Numerics/System/Numerics/BigInteger.cs

// ======================================
// This class is intended to be immutable
// ======================================

// Note that this class 'BigInteger' depends on 'BigIntegerLib.h',
//    and a possible implementation is 'BigIntegerLib.cpp'
// This is done to use C-library style from external world.
//
// Oon the other hand, file 'BigInteger.h' is another possibility, having implementations:
//   - BigIntegerGMP.cpp
//   - BigIntegerMono.cpp
//
// Check the namespaces: 'csbigintegerlib' (for C-style) and 'csbiginteger' (for C++ GMP/Mono)
//

namespace csbigintegerlib {
//
// This class depends on 'csBigIntegerLib.h' (C-style implementation)
// A possible implementation (on C++) is 'BigIntegerLib.cpp', but you can use others.
//

using cs_vbyte = csbiginteger::cs_vbyte;

class BigInteger final
{
private:
   // internal data (vector of bytes) in big-endian format (for readability)
   // efficiency is not important at this moment, correctness and portability is!
   // TODO: perhaps it's better to store in little-endian format... see which methods are affected.
   cs_vbyte _data;

public:
   // size in bytes
   int Length() const
   {
      return _data.size();
   }

   // copy internal bytes (in little-endian) to external array vr. returns 'true' if ok, 'false' if problems.
   bool CopyTo(cs_byte* vr, int sz_vr) const
   {
      // check if size is enough
      if (sz_vr < Length())
         return false;
      cs_vbyte data = _data;                  // big-endian
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
   BigInteger() noexcept
     : _data(cs_vbyte(1, 0x00))
   {
      // not using lib here
   }

   // copy constructor
   BigInteger(const BigInteger& copy) noexcept
     : _data(copy._data)
   {
   }

   // move constructor
   BigInteger(BigInteger&& corpse) noexcept
     : _data(std::move(corpse._data))
   {
   }

   // destructor
   //virtual ~BigInteger();

   // default is base 10
   // allowed base 2
   // if base 16, prefix '0x' is optional. input always big-endian
   BigInteger(std::string str, int base = 10)
   {
      // initialize big integer and return its size (in bytes). output vr must be pre-allocated
      // extern "C" int32 csbiginteger_init_s(char* value, int base, byte* vr, int sz_vr);
      cs_vbyte local_data(str.length() + 2, 0); // ESTIMATE SIZE... TODO: VERIFY!
      cs_int32 realSize = csbiginteger_init_s((char*)str.c_str(), base, local_data.data(), local_data.size());
      _data = cs_vbyte(local_data.begin(), local_data.begin() + realSize);
      std::reverse(_data.begin(), _data.end()); // to little-endian
   }

   BigInteger(cs_int32 value)
     : BigInteger(std::to_string(value), 10)
   {
   }

   BigInteger(cs_int64 value)
     : BigInteger(std::to_string(value), 10)
   {
   }

private:
   std::string float_to_string(float f)
   {
      std::stringstream ss;
      ss << std::fixed << std::setprecision(0) << f;
      std::string s(ss.str());
      return s;
   }

public:
   // from single-precision
   BigInteger(float f)
     : BigInteger(float_to_string(f), 10)
   {
   }

   //BigInteger(float f) :
   //BigInteger(std::to_string((int)f), 10)
   //{
   //}

   // byte data in little-endian format (by default).
   BigInteger(cs_vbyte data, bool isUnsigned = false, bool isBigEndian = false)
     : _data(data)
   {
      if (_data.size() == 0)
         _data.push_back(0x00); // default is zero, not Error

      if (!isBigEndian)
         reverse(_data.begin(), _data.end()); // to big-endian

      if (isUnsigned) {
         this->toUnsigned();
         //while ((_data.size() > 0) && (_data[0] == 0))
         //   _data.erase(_data.begin() + 0);
      }
   }

   // helper method (TODO: remove)
   void toUnsigned()
   {
      if (Sign() < 0) {
         cs_vbyte zero = { 0x00 };
         _data.insert(_data.begin() + 0, zero.begin(), zero.end());
      }
   }

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
   bool operator<(const BigInteger& big) const
   {
      // extern "C" bool csbiginteger_lt(byte* big1, int sz_big1, byte* big2, int sz_big2);
      cs_vbyte data = this->_data;              // copy
      std::reverse(data.begin(), data.end());   // to little endian
      cs_vbyte data2 = big._data;               // copy
      std::reverse(data2.begin(), data2.end()); // to little endian
      return csbiginteger_lt((cs_byte*)data.data(), data.size(), (cs_byte*)data2.data(), data2.size());
   }

   bool operator<=(const BigInteger& big) const
   {
      return ((*this) == big) || ((*this) < big); // where is spaceship operator??
   }

   // depends on external implementation
   bool operator>(const BigInteger& big) const
   {
      // extern "C" bool csbiginteger_gt(byte* big1, int sz_big1, byte* big2, int sz_big2);
      cs_vbyte data = this->_data;              // copy
      std::reverse(data.begin(), data.end());   // to little endian
      cs_vbyte data2 = big._data;               // copy
      std::reverse(data2.begin(), data2.end()); // to little endian
      return csbiginteger_gt((cs_byte*)data.data(), data.size(), (cs_byte*)data2.data(), data2.size());
   }

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

   // this one is little-endian by default
   cs_vbyte ToByteArray(bool isUnsigned = false, bool isBigEndian = false) const
   {
      cs_vbyte rdata = this->_data; // big-endian
      if (isUnsigned) {
         while ((rdata.size() > 0) && (rdata[0] == 0))
            rdata.erase(rdata.begin() + 0);
      }
      if (!isBigEndian) // little-endian
         std::reverse(rdata.begin(), rdata.end());
      return rdata; // do NOT move... may prevent "lucky" copy ellision
   }

   // this one is big-endian (prefixed 0x, to enforce hex format)
   std::string ToString(int base = 16) const
   {
      if (base == 16) {
         std::stringstream ss;
         ss << "0x" << csbiginteger::Helper::revertHexString(this->toHexStr()); // to big-endian
         return ss.str();
      }

      if (base == 2) {
         std::stringstream ss;
         for (unsigned i = 0; i < _data.size(); i++)
            ss << csbiginteger::Helper::parseBin(_data[i]); // byte to binary (TODO: verify if size is 8)
         return ss.str();
      }

      // base 10
      return toStringBase10();
   }

private:
   std::string toStringBase10() const
   {
      // ToString(base). input vb and output sr must be pre-allocated (return indicates failure, 'true' is fine)
      //extern "C" bool csbiginteger_to_string(byte* vb, int sz_vb, int base, char* sr, int sz_sr);
      std::string s(this->_data.size() * 5, ' '); // TODO: CHECK IF IT'S ENOUGH!
      //
      // ToString(base). input vb and output sr must be pre-allocated (return indicates failure, 'true' is fine)
      //extern "C" bool
      //csbiginteger_to_string(byte* vb, int sz_vb, int base, char* sr, int sz_sr);
      cs_vbyte data = this->_data;            // copy
      std::reverse(data.begin(), data.end()); // to little endian
      bool good = csbiginteger_to_string((cs_byte*)data.data(), data.size(), 10, (char*)s.c_str(), s.length());
      csbiginteger::Helper::rtrim(s);
      if (!good) {
         std::cout << "csBigIntegerLibClass WARNING: bad toStringBase10()" << std::endl;
         return "";
      }
      return s;
   }

public:
   // native int32 format
   cs_int32 toInt() const
   {
      // toInt(). input vb must be pre-allocated
      //extern "C" int csbiginteger_to_int(byte* vb, int sz_vb);
      cs_vbyte data = this->_data;            // copy
      std::reverse(data.begin(), data.end()); // to little endian
      return csbiginteger_to_int((cs_byte*)data.data(), data.size());
   }

   // native int64 format
   cs_int64 toLong() const
   {
      //extern "C" long csbiginteger_to_long(byte* vb, int sz_vb);
      cs_vbyte data = this->_data;            // copy
      std::reverse(data.begin(), data.end()); // to little endian
      return csbiginteger_to_long((cs_byte*)data.data(), data.size());
   }

   cs_int32 Sign() const
   {
      if ((*this) == BigInteger::Zero)
         return 0;
      else if ((*this) < BigInteger::Zero)
         return -1;
      else
         return 1;
   }

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
   BigInteger operator+(const BigInteger& big2) const
   {
      if (this->IsError() || big2.IsError())
         return Error;
      // perform big1 + big2 and return its size (in bytes). output vr must be pre-allocated
      //extern "C" int32
      //csbiginteger_add(byte* big1, int sz_big1, byte* big2, int sz_big2, byte* vr, int sz_vr);
      cs_vbyte local_data(this->_data.size() + big2._data.size() + 2, 0);
      cs_vbyte data = this->_data;              // copy
      std::reverse(data.begin(), data.end());   // to little endian
      cs_vbyte data2 = big2._data;              // copy
      std::reverse(data2.begin(), data2.end()); // to little endian
      cs_int32 realSize = csbiginteger_add((cs_byte*)data.data(), data.size(), (cs_byte*)data2.data(), data2.size(), (cs_byte*)local_data.data(), local_data.size());
      BigInteger bigNew(cs_vbyte(local_data.begin(), local_data.begin() + realSize));
      return bigNew;
   }

   BigInteger
   operator+(cs_int64 l2) const
   {
      BigInteger other(l2);
      return (*this) + other;
   }

   // immutable??
   BigInteger& operator+=(int i2);

   // depends on external implementation
   BigInteger operator-(const BigInteger& big2) const
   {
      if (this->IsError() || big2.IsError())
         return Error;
      // perform big1 - big2 and return its size (in bytes). output vr must be pre-allocated
      //extern "C" int32
      //csbiginteger_sub(byte* big1, int sz_big1, byte* big2, int sz_big2, byte* vr, int sz_vr);
      cs_vbyte local_data(this->_data.size() + big2._data.size() + 2, 0);
      cs_vbyte data = this->_data;              // copy
      std::reverse(data.begin(), data.end());   // to little endian
      cs_vbyte data2 = big2._data;              // copy
      std::reverse(data2.begin(), data2.end()); // to little endian
      cs_int32 realSize = csbiginteger_sub((cs_byte*)data.data(), data.size(), (cs_byte*)data2.data(), data2.size(), (cs_byte*)local_data.data(), local_data.size());
      BigInteger bigNew(cs_vbyte(local_data.begin(), local_data.begin() + realSize));
      return bigNew;
   }

   BigInteger operator-(cs_int64 l2) const
   {
      BigInteger other(l2);
      return (*this) - other;
   }

   // immutable ??
   BigInteger& operator-=(cs_int32 i2);

   // negate (unary)
   BigInteger operator-() const
   {
      return BigInteger::Zero - (*this);
   }

   // depends on external implementation
   BigInteger operator*(const BigInteger& big2) const
   {
      if (this->IsError() || big2.IsError())
         return Error;
      // perform big1 * big2 and return its size (in bytes). output vr must be pre-allocated
      //extern "C" int32
      //csbiginteger_mul(byte* big1, int sz_big1, byte* big2, int sz_big2, byte* vr, int sz_vr);
      cs_vbyte local_data(this->_data.size() * big2._data.size() + 2, 0);
      cs_vbyte data = this->_data;              // copy
      std::reverse(data.begin(), data.end());   // to little endian
      cs_vbyte data2 = big2._data;              // copy
      std::reverse(data2.begin(), data2.end()); // to little endian
      cs_int32 realSize = csbiginteger_mul((cs_byte*)data.data(), data.size(), (cs_byte*)data2.data(), data2.size(), (cs_byte*)local_data.data(), local_data.size());
      BigInteger bigNew(cs_vbyte(local_data.begin(), local_data.begin() + realSize));
      return bigNew;
   }

   BigInteger operator*(cs_int64 l2) const
   {
      BigInteger other(l2);
      return (*this) * other;
   }

   // depends on external implementation
   BigInteger operator/(const BigInteger& big2) const
   {
      if (this->IsError() || big2.IsError() || big2.IsZero())
         return Error;
      // perform big1 / big2 and return its size (in bytes). output vr must be pre-allocated
      //extern "C" int32
      //csbiginteger_div(byte* big1, int sz_big1, byte* big2, int sz_big2, byte* vr, int sz_vr);
      cs_vbyte local_data(this->_data.size() + big2._data.size() + 2, 0);
      cs_vbyte data = this->_data;              // copy
      std::reverse(data.begin(), data.end());   // to little endian
      cs_vbyte data2 = big2._data;              // copy
      std::reverse(data2.begin(), data2.end()); // to little endian
      cs_int32 realSize = csbiginteger_div((cs_byte*)data.data(), data.size(), (cs_byte*)data2.data(), data2.size(), (cs_byte*)local_data.data(), local_data.size());
      BigInteger bigNew(cs_vbyte(local_data.begin(), local_data.begin() + realSize));
      return bigNew;
   }

   BigInteger operator/(cs_int64 l2) const
   {
      BigInteger other(l2);
      return (*this) / other;
   }

   // depends on external implementation
   BigInteger operator%(const BigInteger& big2) const
   {
      if (this->IsError() || big2.IsError())
         return Error;
      // perform big1 % big2 and return its size (in bytes). output vr must be pre-allocated
      //extern "C" int32
      //csbiginteger_mod(byte* big1, int sz_big1, byte* big2, int sz_big2, byte* vr, int sz_vr);
      cs_vbyte local_data(this->_data.size() + big2._data.size() + 2, 0);
      cs_vbyte data = this->_data;              // copy
      std::reverse(data.begin(), data.end());   // to little endian
      cs_vbyte data2 = big2._data;              // copy
      std::reverse(data2.begin(), data2.end()); // to little endian
      cs_int32 realSize = csbiginteger_mod((cs_byte*)data.data(), data.size(), (cs_byte*)data2.data(), data2.size(), (cs_byte*)local_data.data(), local_data.size());
      BigInteger bigNew(cs_vbyte(local_data.begin(), local_data.begin() + realSize));
      return bigNew;
   }

   BigInteger operator%(cs_int64 l2) const
   {
      BigInteger other(l2);
      return (*this) / other;
   }

   // immutable??
   BigInteger& operator<<=(cs_int32 i2);

   // depends on external implementation
   BigInteger operator<<(const BigInteger& big2) const
   {
      if (this->IsError() || big2.IsError())
         return Error;
      // perform big1 << big2 and return its size (in bytes). output vr must be pre-allocated
      //extern "C" int32
      //csbiginteger_shl(byte* big1, int sz_big1, byte* big2, int sz_big2, byte* vr, int sz_vr);
      cs_vbyte local_data(this->_data.size() + big2._data.size() + 2, 0);
      cs_vbyte data = this->_data;              // copy
      std::reverse(data.begin(), data.end());   // to little endian
      cs_vbyte data2 = big2._data;              // copy
      std::reverse(data2.begin(), data2.end()); // to little endian
      cs_int32 realSize = csbiginteger_shl((cs_byte*)data.data(), data.size(), (cs_byte*)data2.data(), data2.size(), (cs_byte*)local_data.data(), local_data.size());
      BigInteger bigNew(cs_vbyte(local_data.begin(), local_data.begin() + realSize));
      return bigNew;
   }

   BigInteger operator<<(cs_int64 l2) const
   {
      BigInteger other(l2);
      return (*this) << other;
   }

   // immutable??
   BigInteger& operator>>=(cs_int32 i2);

   // depends on external implementation
   BigInteger operator>>(const BigInteger& big2) const
   {
      if (this->IsError() || big2.IsError())
         return Error;
      // perform big1 >> big2 and return its size (in bytes). output vr must be pre-allocated
      //extern "C" int32
      //csbiginteger_shr(byte* big1, int sz_big1, byte* big2, int sz_big2, byte* vr, int sz_vr);
      cs_vbyte local_data(this->_data.size() + big2._data.size() + 2, 0);
      cs_vbyte data = this->_data;              // copy
      std::reverse(data.begin(), data.end());   // to little endian
      cs_vbyte data2 = big2._data;              // copy
      std::reverse(data2.begin(), data2.end()); // to little endian
      cs_int32 realSize = csbiginteger_shr((cs_byte*)data.data(), data.size(), (cs_byte*)data2.data(), data2.size(), (cs_byte*)local_data.data(), local_data.size());
      BigInteger bigNew(cs_vbyte(local_data.begin(), local_data.begin() + realSize));
      return bigNew;
   }
   BigInteger operator>>(cs_int64 l2) const
   {
      BigInteger other(l2);
      return (*this) >> other;
   }

   // what else is needed here?

   // Utils

   // pow allows int32 positive exponent (negative will generate BigInteger::Error)
   static BigInteger Pow(BigInteger value, cs_int32 exponent)
   {
      // according to C# spec, only non-negative int32 values accepted here
      if (exponent < 0)
         return BigInteger::Error;
      // perform big ^ int32 and return its size (in bytes). output vr must be pre-allocated
      //extern "C" int32
      //csbiginteger_pow(byte* big, int sz_big, int exp, byte* vr, int sz_vr);
      cs_vbyte local_data(value._data.size() * (2 * ::abs(exponent) + 2), 0);
      cs_vbyte data = value._data;            // copy
      std::reverse(data.begin(), data.end()); // to little endian
      cs_int32 realSize = csbiginteger_pow((cs_byte*)data.data(), data.size(), exponent, (cs_byte*)local_data.data(), local_data.size());
      BigInteger bigNew(cs_vbyte(local_data.begin(), local_data.begin() + realSize));
      return bigNew;
   }

   static BigInteger Multiply(BigInteger value1, BigInteger value2)
   {
      return value1 * value2;
   }

public:
   // object accessible helper method
   // hex string is returned on little-endian
   std::string toHexStr() const
   {
      cs_vbyte data = this->ToByteArray();                     // little-endian
      std::string s = csbiginteger::Helper::toHexString(data); // TODO: take from C
      return s;
   }

   bool IsEven() const
   {
      BigInteger bigmod = (*this) % BigInteger{ 2 };
      return bigmod == BigInteger::Zero;
   }

   BigInteger& operator=(const BigInteger& other)
   {
      if (this == &other)
         return *this;
      this->_data = other._data;
      return *this;
   }

   BigInteger& operator=(BigInteger&& m_other)
   {
      this->_data = std::move(m_other._data);
      m_other._data.clear();
      return *this;
   }

   static BigInteger DivRem(const BigInteger& dividend, const BigInteger& divisor, BigInteger& out_remainder)
   {
      out_remainder = dividend % divisor;
      return dividend / divisor;
   }

private:
   const static BigInteger error();

public:
   const static BigInteger Error; // error biginteger (empty internal bytearray)
};

const BigInteger BigInteger::Zero = BigInteger(0);
const BigInteger BigInteger::One = BigInteger(1);
const BigInteger BigInteger::MinusOne = BigInteger(-1);
//
const BigInteger
BigInteger::error()
{
   BigInteger big;
   big._data = cs_vbyte(0); // empty array is error
   return big;
}
//
const BigInteger BigInteger::Error = error();

} // namespace csbigintegerlib

#endif // CSBIGINTEGERLIB_BIGINTEGER_HPP
