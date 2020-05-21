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
   BigInteger()
     : _data(vbyte(1, 0x00))
   {
      // not using lib here
   }

   // copy constructor
   BigInteger(const BigInteger& copy)
     : _data(copy._data)
   {
   }

   // move constructor
   BigInteger(BigInteger&& corpse)
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
      vbyte local_data(str.length() + 2, 0); // ESTIMATE SIZE... TODO: VERIFY!
      int32 realSize = csbiginteger_init_s((char*)str.c_str(), base, local_data.data(), local_data.size());
      _data = vbyte(local_data.begin(), local_data.begin() + realSize);
      std::reverse(_data.begin(), _data.end()); // to little-endian
   }

   BigInteger(int32 value)
     : BigInteger(std::to_string(value), 10)
   {
   }

   BigInteger(int64 value)
     : BigInteger(std::to_string(value), 10)
   {
   }

   // from single-precision
   BigInteger(float f)
     : BigInteger((int64)f)
   {
   }

   //BigInteger(float f) :
   //BigInteger(std::to_string((int)f), 10)
   //{
   //}

   // byte data in little-endian format
   BigInteger(vbyte data)
     : _data(data)
   {
      if (_data.size() == 0)
         _data.push_back(0x00);            // default is zero, not Error
      reverse(_data.begin(), _data.end()); // to big-endian
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
      vbyte data = this->_data;                 // copy
      std::reverse(data.begin(), data.end());   // to little endian
      vbyte data2 = big._data;                  // copy
      std::reverse(data2.begin(), data2.end()); // to little endian
      return csbiginteger_lt((byte*)data.data(), data.size(), (byte*)data2.data(), data2.size());
   }

   bool operator<=(const BigInteger& big) const
   {
      return ((*this) == big) || ((*this) < big); // where is spaceship operator??
   }

   // depends on external implementation
   bool operator>(const BigInteger& big) const
   {
      // extern "C" bool csbiginteger_gt(byte* big1, int sz_big1, byte* big2, int sz_big2);
      vbyte data = this->_data;                 // copy
      std::reverse(data.begin(), data.end());   // to little endian
      vbyte data2 = big._data;                  // copy
      std::reverse(data2.begin(), data2.end()); // to little endian
      return csbiginteger_gt((byte*)data.data(), data.size(), (byte*)data2.data(), data2.size());
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
      std::string s(this->_data.size() * 4, ' '); // TODO: CHECK IF IT'S ENOUGH!
      //
      // ToString(base). input vb and output sr must be pre-allocated (return indicates failure, 'true' is fine)
      //extern "C" bool
      //csbiginteger_to_string(byte* vb, int sz_vb, int base, char* sr, int sz_sr);
      vbyte data = this->_data;               // copy
      std::reverse(data.begin(), data.end()); // to little endian
      bool good = csbiginteger_to_string((byte*)data.data(), data.size(), 10, (char*)s.c_str(), s.length());
      csbiginteger::Helper::rtrim(s);
      if (!good) {
         std::cout << "csBigIntegerLibClass WARNING: bad toStringBase10()" << std::endl;
         return "";
      }
      return s;
   }

public:
   // native int32 format
   int32 toInt() const
   {
      // toInt(). input vb must be pre-allocated
      //extern "C" int csbiginteger_to_int(byte* vb, int sz_vb);
      vbyte data = this->_data;               // copy
      std::reverse(data.begin(), data.end()); // to little endian
      return csbiginteger_to_int((byte*)data.data(), data.size());
   }

   // native int64 format
   int64 toLong() const
   {
      //extern "C" long csbiginteger_to_long(byte* vb, int sz_vb);
      vbyte data = this->_data;               // copy
      std::reverse(data.begin(), data.end()); // to little endian
      return csbiginteger_to_long((byte*)data.data(), data.size());
   }

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
   BigInteger operator+(const BigInteger& big2) const
   {
      if (this->IsError() || big2.IsError())
         return Error;
      // perform big1 + big2 and return its size (in bytes). output vr must be pre-allocated
      //extern "C" int32
      //csbiginteger_add(byte* big1, int sz_big1, byte* big2, int sz_big2, byte* vr, int sz_vr);
      vbyte local_data(this->_data.size() + big2._data.size() + 2, 0);
      vbyte data = this->_data;                 // copy
      std::reverse(data.begin(), data.end());   // to little endian
      vbyte data2 = big2._data;                 // copy
      std::reverse(data2.begin(), data2.end()); // to little endian
      int32 realSize = csbiginteger_add((byte*)data.data(), data.size(), (byte*)data2.data(), data2.size(), (byte*)local_data.data(), local_data.size());
      BigInteger bigNew(vbyte(local_data.begin(), local_data.begin() + realSize));
      return bigNew;
   }

   BigInteger operator+(long l2) const
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
      vbyte local_data(this->_data.size() + big2._data.size() + 2, 0);
      vbyte data = this->_data;                 // copy
      std::reverse(data.begin(), data.end());   // to little endian
      vbyte data2 = big2._data;                 // copy
      std::reverse(data2.begin(), data2.end()); // to little endian
      int32 realSize = csbiginteger_sub((byte*)data.data(), data.size(), (byte*)data2.data(), data2.size(), (byte*)local_data.data(), local_data.size());
      BigInteger bigNew(vbyte(local_data.begin(), local_data.begin() + realSize));
      return bigNew;
   }

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
   BigInteger operator*(const BigInteger& big2) const
   {
      if (this->IsError() || big2.IsError())
         return Error;
      // perform big1 * big2 and return its size (in bytes). output vr must be pre-allocated
      //extern "C" int32
      //csbiginteger_mul(byte* big1, int sz_big1, byte* big2, int sz_big2, byte* vr, int sz_vr);
      vbyte local_data(this->_data.size() + big2._data.size() + 2, 0);
      vbyte data = this->_data;                 // copy
      std::reverse(data.begin(), data.end());   // to little endian
      vbyte data2 = big2._data;                 // copy
      std::reverse(data2.begin(), data2.end()); // to little endian
      int32 realSize = csbiginteger_mul((byte*)data.data(), data.size(), (byte*)data2.data(), data2.size(), (byte*)local_data.data(), local_data.size());
      BigInteger bigNew(vbyte(local_data.begin(), local_data.begin() + realSize));
      return bigNew;
   }

   BigInteger operator*(long l2) const
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
      vbyte local_data(this->_data.size() + big2._data.size() + 2, 0);
      vbyte data = this->_data;                 // copy
      std::reverse(data.begin(), data.end());   // to little endian
      vbyte data2 = big2._data;                 // copy
      std::reverse(data2.begin(), data2.end()); // to little endian
      int32 realSize = csbiginteger_div((byte*)data.data(), data.size(), (byte*)data2.data(), data2.size(), (byte*)local_data.data(), local_data.size());
      BigInteger bigNew(vbyte(local_data.begin(), local_data.begin() + realSize));
      return bigNew;
   }

   BigInteger operator/(long l2) const
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
      vbyte local_data(this->_data.size() + big2._data.size() + 2, 0);
      vbyte data = this->_data;                 // copy
      std::reverse(data.begin(), data.end());   // to little endian
      vbyte data2 = big2._data;                 // copy
      std::reverse(data2.begin(), data2.end()); // to little endian
      int32 realSize = csbiginteger_mod((byte*)data.data(), data.size(), (byte*)data2.data(), data2.size(), (byte*)local_data.data(), local_data.size());
      BigInteger bigNew(vbyte(local_data.begin(), local_data.begin() + realSize));
      return bigNew;
   }

   BigInteger operator%(long l2) const
   {
      BigInteger other(l2);
      return (*this) / other;
   }

   // immutable??
   BigInteger& operator<<=(int i2);

   // depends on external implementation
   BigInteger operator<<(const BigInteger& big2) const
   {
      if (this->IsError() || big2.IsError())
         return Error;
      // perform big1 << big2 and return its size (in bytes). output vr must be pre-allocated
      //extern "C" int32
      //csbiginteger_shl(byte* big1, int sz_big1, byte* big2, int sz_big2, byte* vr, int sz_vr);
      vbyte local_data(this->_data.size() + big2._data.size() + 2, 0);
      vbyte data = this->_data;                 // copy
      std::reverse(data.begin(), data.end());   // to little endian
      vbyte data2 = big2._data;                 // copy
      std::reverse(data2.begin(), data2.end()); // to little endian
      int32 realSize = csbiginteger_shl((byte*)data.data(), data.size(), (byte*)data2.data(), data2.size(), (byte*)local_data.data(), local_data.size());
      BigInteger bigNew(vbyte(local_data.begin(), local_data.begin() + realSize));
      return bigNew;
   }

   BigInteger operator<<(long l2) const
   {
      BigInteger other(l2);
      return (*this) << other;
   }

   // immutable??
   BigInteger& operator>>=(int i2);

   // depends on external implementation
   BigInteger operator>>(const BigInteger& big2) const
   {
      if (this->IsError() || big2.IsError())
         return Error;
      // perform big1 >> big2 and return its size (in bytes). output vr must be pre-allocated
      //extern "C" int32
      //csbiginteger_shr(byte* big1, int sz_big1, byte* big2, int sz_big2, byte* vr, int sz_vr);
      vbyte local_data(this->_data.size() + big2._data.size() + 2, 0);
      vbyte data = this->_data;                 // copy
      std::reverse(data.begin(), data.end());   // to little endian
      vbyte data2 = big2._data;                 // copy
      std::reverse(data2.begin(), data2.end()); // to little endian
      int32 realSize = csbiginteger_shr((byte*)data.data(), data.size(), (byte*)data2.data(), data2.size(), (byte*)local_data.data(), local_data.size());
      BigInteger bigNew(vbyte(local_data.begin(), local_data.begin() + realSize));
      return bigNew;
   }
   BigInteger operator>>(long l2) const
   {
      BigInteger other(l2);
      return (*this) >> other;
   }

   // what else is needed here?

   // Utils

   // pow allows int32 positive exponent (negative will generate BigInteger::Error)
   static BigInteger Pow(BigInteger value, int exponent)
   {
      // according to C# spec, only non-negative int32 values accepted here
      if (exponent < 0)
         return BigInteger::Error;
      // perform big ^ int32 and return its size (in bytes). output vr must be pre-allocated
      //extern "C" int32
      //csbiginteger_pow(byte* big, int sz_big, int exp, byte* vr, int sz_vr);
      vbyte local_data(value._data.size() * (::abs(exponent) + 2), 0);
      vbyte data = value._data;               // copy
      std::reverse(data.begin(), data.end()); // to little endian
      int32 realSize = csbiginteger_pow((byte*)data.data(), data.size(), exponent, (byte*)local_data.data(), local_data.size());
      BigInteger bigNew;
      bigNew._data = vbyte(local_data.begin(), local_data.begin() + realSize);
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
      vbyte data = this->ToByteArray();                        // little-endian
      std::string s = csbiginteger::Helper::toHexString(data); // TODO: take from C
      return s;
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
   big._data = vbyte(0); // empty array is error
   return big;
}
//
const BigInteger BigInteger::Error = error();

} // namespace csbigintegerlib

#endif // CSBIGINTEGERLIB_BIGINTEGER_HPP
