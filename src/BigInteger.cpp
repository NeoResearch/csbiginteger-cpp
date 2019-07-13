
#include "BigInteger.h"

// system
#include <iostream> // todo: remove

// using gmp as internal computation method
// TODO: abandon this in favor of more portable libraries
// sudo apt install libgmp (or libgmp-dev)
#include <gmp.h>
#include <gmpxx.h>

#include <assert.h>

// Ported from
// - https://referencesource.microsoft.com/#System.Numerics/System/Numerics/BigInteger.cs

using namespace std;
using namespace csbiginteger;

// input is raw little-endian format
mpz_class
csBigIntegerMPZparse(vbyte n);

// string parse
mpz_class
csBigIntegerMPZparses(string n, int base);

// get bitstring from mpz bignum non-negative object
string
csBigIntegerGetBitsFromNonNegativeMPZ(mpz_class big);

// get big-endian bytearray from mpz bignum (positive or negative)
vbyte
csBigIntegerGetBytesFromMPZ(mpz_class big);

// ==================== END MPZ =======================

const BigInteger BigInteger::Zero = BigInteger(0);
const BigInteger BigInteger::One = BigInteger(1);
const BigInteger BigInteger::MinusOne = BigInteger(-1);
const BigInteger BigInteger::Error = error();

const BigInteger
BigInteger::error()
{
   BigInteger big;
   big._data = vbyte(0); // empty array is error
   return big;
}

// nothing to initialize on empty constructor ('_data' is already empty)
BigInteger::BigInteger()
  : _data(vbyte(1, 0x00))
{
}

// copy
BigInteger::BigInteger(const BigInteger& copy)
  : _data(copy._data)
{
}

// move
BigInteger::BigInteger(BigInteger&& corpse)
  : _data(std::move(corpse._data))
{
}

// destructor (nothing to do)
BigInteger::~BigInteger()
{
}

// input byte data in little-endian format
BigInteger::BigInteger(vbyte data)
  : _data(data)
{
   if (_data.size() == 0)
      _data.push_back(0x00);            // default is zero, not Error
   reverse(_data.begin(), _data.end()); // to big-endian
}

// default is base 10
// allows base 2
// if base 16, prefix '0x' indicates big-endian, otherwise is little-endian
BigInteger::BigInteger(string str, int base)
{
   mpz_class a = csBigIntegerMPZparses(str, base);
   _data = csBigIntegerGetBytesFromMPZ(a);
}

BigInteger::BigInteger(int32 val)
{
   mpz_class a = val;
   _data = csBigIntegerGetBytesFromMPZ(a);
}

BigInteger::BigInteger(int64 val)
{
   mpz_class a = val;
   _data = csBigIntegerGetBytesFromMPZ(a);
}

int32
BigInteger::toInt() const
{
   vbyte vb = this->ToByteArray(); // little-endian
   mpz_class a = csBigIntegerMPZparse(vb);
   int32 i = a.get_ui(); // unsigned int
   if (a < 0)
      i *= -1;
   return i;
}

int64
BigInteger::toLong() const
{
   vbyte vb = this->ToByteArray(); // little-endian
   mpz_class a = csBigIntegerMPZparse(vb);
   int64 i = a.get_si(); // signed long int
   return i;
}

bool
BigInteger::operator>(const BigInteger& big2) const
{
   if (this->IsError() || big2.IsError())
      return false;

   mpz_class bThis = csBigIntegerMPZparse(this->ToByteArray()); // parse from little-endian
   mpz_class bOther = csBigIntegerMPZparse(big2.ToByteArray()); // parse from little-endian

   bool r = (bThis > bOther); // result
   return r;
}

bool
BigInteger::operator<(const BigInteger& big2) const
{
   if (this->IsError() || big2.IsError()) {
      return false;
   }

   mpz_class bThis = csBigIntegerMPZparse(this->ToByteArray()); // parse from little-endian
   mpz_class bOther = csBigIntegerMPZparse(big2.ToByteArray()); // parse from little-endian

   bool r = (bThis < bOther); // result
   return r;
}

// ----------------- arithmetic ---------------------

BigInteger
BigInteger::operator+(const BigInteger& big2) const
{
   if (this->IsError() || big2.IsError())
      return Error;

   mpz_class bThis = csBigIntegerMPZparse(this->ToByteArray()); // parse from little-endian
   mpz_class bOther = csBigIntegerMPZparse(big2.ToByteArray()); // parse from little-endian
   BigInteger r;                                                // result
   r._data = csBigIntegerGetBytesFromMPZ(bThis + bOther);       // get big-endian
   return std::move(r);
}

BigInteger
BigInteger::operator-(const BigInteger& big2) const
{
   if (this->IsError() || big2.IsError())
      return Error;

   mpz_class bThis = csBigIntegerMPZparse(this->ToByteArray()); // parse from little-endian
   mpz_class bOther = csBigIntegerMPZparse(big2.ToByteArray()); // parse from little-endian
   BigInteger r;                                                // result
   r._data = csBigIntegerGetBytesFromMPZ(bThis - bOther);       // get big-endian
   return std::move(r);
}

BigInteger
  BigInteger::operator*(const BigInteger& big2) const
{
   if (this->IsError() || big2.IsError())
      return Error;

   mpz_class bThis = csBigIntegerMPZparse(this->ToByteArray()); // parse from little-endian
   mpz_class bOther = csBigIntegerMPZparse(big2.ToByteArray()); // parse from little-endian
   BigInteger r;                                                // result
   r._data = csBigIntegerGetBytesFromMPZ(bThis * bOther);       // get big-endian
   return std::move(r);
}

BigInteger
BigInteger::operator/(const BigInteger& big2) const
{
   if (this->IsError() || big2.IsError() || big2.IsZero())
      return Error;
   mpz_class bThis = csBigIntegerMPZparse(this->ToByteArray()); // parse from little-endian
   mpz_class bOther = csBigIntegerMPZparse(big2.ToByteArray()); // parse from little-endian
   BigInteger r;                                                // result
   r._data = csBigIntegerGetBytesFromMPZ(bThis / bOther);       // get big-endian
   return std::move(r);
}

BigInteger
BigInteger::operator%(const BigInteger& big2) const
{
   if (this->IsError() || big2.IsError() || big2.IsZero())
      return Error;

   mpz_class bThis = csBigIntegerMPZparse(this->ToByteArray()); // parse from little-endian
   mpz_class bOther = csBigIntegerMPZparse(big2.ToByteArray()); // parse from little-endian
   BigInteger r;                                                // result
   r._data = csBigIntegerGetBytesFromMPZ(bThis % bOther);       // get big-endian
   return std::move(r);
}

BigInteger
BigInteger::operator<<(const BigInteger& big2) const
{
   if (this->IsError() || big2.IsError())
      return Error;
   if (big2 < Zero)
      return (*this) >> -big2;

   mpz_class bThis = csBigIntegerMPZparse(this->ToByteArray());  // parse from little-endian
   BigInteger r;                                                 // result
   r._data = csBigIntegerGetBytesFromMPZ(bThis << big2.toInt()); // get big-endian
   return std::move(r);
}

BigInteger
BigInteger::operator>>(const BigInteger& big2) const
{
   if (this->IsError() || big2.IsError())
      return Error;
   if (big2 < Zero)
      return (*this) << -big2;

   mpz_class bThis = csBigIntegerMPZparse(this->ToByteArray());  // parse from little-endian
   BigInteger r;                                                 // result
   r._data = csBigIntegerGetBytesFromMPZ(bThis >> big2.toInt()); // get big-endian
   return std::move(r);
}

// =================== BEGIN MPZ AGAIN =======================

string
BigInteger::toStringBase10() const
{
   mpz_class bThis = csBigIntegerMPZparse(this->ToByteArray()); // parse from little-endian
   return bThis.get_str(10);
}

// assumes big >= 0
string
csBigIntegerGetBitsFromNonNegativeMPZ(mpz_class big)
{
   string sbin;
   while (big > 0) {
      mpz_class rest = (big % 2);
      sbin.insert(0, (rest.get_ui() == 0 ? string("0") : string("1")));
      big = big / 2;
   }
   return sbin;
}

vbyte
csBigIntegerGetBytesFromMPZ(mpz_class big)
{
   // check if positive or negative
   if (big >= 0) {
      // -------------------
      // positive conversion
      // -------------------
      vbyte v;
      while (big > 0) {
         mpz_class rest = (big % 256);
         v.push_back((byte)rest.get_ui());
         big = big / 256;
      }

      // added in little-endian format (backwards)
      string leHex = Helper::toHexString(v);
      if (leHex.length() == 0)
         leHex = "00";
      // check if became negative
      if (Helper::checkNegativeBit(leHex)) {
         v.push_back(0); // guarantee non-negative
      }

      // v is added backwards (little-endian), must reverse (to big-endian)
      reverse(v.begin(), v.end());
      if (v.size() == 0)
         v.push_back(0x00);
      // finished
      return std::move(v);
   } else {
      // -------------------
      // negative conversion
      // -------------------
      // turn into positive
      mpz_class x = big * (-1);
      // ========================
      // perform two's complement
      // ========================
      // convert to binary
      vbyte vx = csBigIntegerGetBytesFromMPZ(x); // positive is easy to convert
      mpz_class bx(Helper::toHexString(vx), 16);
      // get binary representation
      std::string y = bx.get_str(2);
      // extra padding for limit cases (avoid overflow)
      y.insert(0, "0"); // prepend

      //guarantee length must be at least 8, or add padding!
      while ((y.length() < 8) || (y.length() % 8 != 0)) {
         y.insert(0, "0"); // prepend
      }
      // invert bits
      std::string y2 = "";
      for (int i = 0; i < y.length(); i++)
         y2 += (y[i] == '0' ? '1' : '0');
      // go back to bigint
      //BigInteger by3(y2, 2); // recursive behavior
      mpz_class by3(y2, 2);
      // sum 1
      mpz_class bby3 = by3 + 1;
      // convert to binary again
      std::string y4 = csBigIntegerGetBitsFromNonNegativeMPZ(bby3);

      //guarantee length must be at least 8, or add padding!
      while (y4.length() < 8) {
         y4.insert(0, "0"); // prepend
      }
      // get in bytes
      vbyte v = Helper::BinToBytes(y4);
      if (v.size() == 0)
         v.push_back(0x00);

      // finished
      return std::move(v);
   }
}

// taken from csBigInteger.js
/*
	Function: parse
	Parse a string or little-endian byte array into a <BigInteger>.

	- "0x" or "0X": *base* = 16
	- "0b": *base* = 2 (?)
	- else: *base* = 10

	Parameters:

		s - The string to parse.
    base - Optional (default is 10)

	Returns:

		a <BigInteger> instance.
*/

// expects vbyte on little-endian format (raw internal format)
mpz_class
csBigIntegerMPZparse(vbyte n)
{
   if (n.size() == 0)
      return mpz_class(0);

   std::string s = Helper::toHexString(n);

   // verify if number is negative (most significant bit)
   if (Helper::checkNegativeBit(s)) {
      // is negative, must handle twos-complement
      mpz_class vint(Helper::revertHexString(s), 16); // as big-endian again
      // get bitstring
      std::string rbitnum = csBigIntegerGetBitsFromNonNegativeMPZ(vint);
      // negate bits
      std::stringstream y2;
      for (int i = 0; i < rbitnum.length(); i++)
         y2 << (rbitnum[i] == '0' ? '1' : '0');
      // to bigint again
      mpz_class by2(y2.str(), 2);
      // add one
      mpz_class by2add = by2 + 1;
      // get negative
      mpz_class finalnum = by2add * (-1);
      // ensure it's negative (TODO: remove)
      assert(finalnum < 0); // must be negative
      // finished
      return finalnum;
   } else {
      // positive is easy (in little-endian format)
      std::string sbig = Helper::revertHexString(s);
      // build bignum in big-endian
      return mpz_class(sbig, 16); // big-endian again
   }
}

mpz_class
csBigIntegerMPZparses(string n, int base)
{
   if (base == 10) {
      if (n.length() == 0)
         n = "0";
      return mpz_class(n, base);
   }

   if (base == 2) {
      if (n.length() == 0)
         n = "0";
      return mpz_class(n, base);
   }

   if (base != 16) {
      cout << "UNSUPPORTED BASE! " << base << endl;
      exit(1);
   }

   // zero padding
   while (n.length() < 2)
      n.insert(0, "0");

   // return bytearray initialized
   vbyte vb;
   // prefix '0x' indicates big-endian, otherwise is little-endian
   if ((n[0] == '0') && (n[1] == 'x')) {
      // removing '0x'
      n = n.substr(2, n.length() - 2);
      vb = Helper::HexToBytes(n);
      reverse(vb.begin(), vb.end()); // to little-endian
   } else {
      vb = Helper::HexToBytes(n); // directly reading little-endian byte array
   }

   // base 16
   return csBigIntegerMPZparse(vb); // vb is little-endian byte array
}
