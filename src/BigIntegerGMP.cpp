// SPDX-License-Identifier:  LGPL-3.0-or-later AND MIT
// Copyright (C) 2020-2022 - csbiginteger-cpp project

#include <csbiginteger/BigInteger.h>

//
// using gmp as internal computation method
// TODO(igormcoelho): abandon this in favor of more portable libraries
// sudo apt install libgmp (or libgmp-dev)
#include <assert.h>
#include <gmp.h>
#include <gmpxx.h>

// c++
#include <iostream>  // TODO(igormcoelho): remove

// Ported from
// -
// https://referencesource.microsoft.com/#System.Numerics/System/Numerics/BigInteger.cs

// using namespace std;
using namespace csbiginteger;  // NOLINT

// input is raw little-endian format
mpz_class csBigIntegerMPZparse(cs_vbyte n);

// string parse
mpz_class csBigIntegerMPZparses(std::string n, int base);

// get bitstring from mpz bignum non-negative object
std::string csBigIntegerGetBitsFromNonNegativeMPZ(mpz_class big);

// get big-endian bytearray from mpz bignum (positive or negative)
cs_vbyte csBigIntegerGetBytesFromMPZ(mpz_class big);

// ==================== END MPZ =======================

std::string BigInteger::getEngine() { return "GMP"; }

const BigInteger BigInteger::error() {
  BigInteger big;
  big._data = cs_vbyte(0);  // empty array is error
  return big;
}

BigInteger BigInteger::Pow(BigInteger value, int exponent) {
  // according to C# spec, only non-negative int32 values accepted here
  if (exponent < 0) return BigInteger::Error();
  mpz_class big1 = csBigIntegerMPZparse(value.ToByteArray());
  mpz_class r;
  uint64_t _exp = exponent;
  mpz_pow_ui(r.get_mpz_t(), big1.get_mpz_t(), _exp);
  cs_vbyte vr = csBigIntegerGetBytesFromMPZ(r);
  reverse(vr.begin(), vr.end());  // to little-endian
  return BigInteger(vr);
}

// default is base 10
// allows base 2
// if base 16, prefix '0x' indicates big-endian, otherwise is little-endian
BigInteger::BigInteger(std::string str, int base) {
  mpz_class a = csBigIntegerMPZparses(str, base);
  _data = csBigIntegerGetBytesFromMPZ(a);
}

BigInteger::BigInteger(float val) {
  mpz_class a = val;

  _data = csBigIntegerGetBytesFromMPZ(a);
}

cs_int32 BigInteger::toInt() const {
  cs_vbyte vb = this->ToByteArray();  // little-endian
  mpz_class a = csBigIntegerMPZparse(vb);
  cs_int32 i = a.get_ui();  // unsigned int
  if (a < 0) i *= -1;
  return i;
}

cs_int64 BigInteger::toLong() const {
  cs_vbyte vb = this->ToByteArray();  // little-endian
  mpz_class a = csBigIntegerMPZparse(vb);
  cs_int64 i = a.get_si();  // signed long int
  return i;
}

bool BigInteger::operator>(const BigInteger& big2) const {
  if (this->IsError() || big2.IsError()) return false;

  mpz_class bThis =
      csBigIntegerMPZparse(this->ToByteArray());  // parse from little-endian
  mpz_class bOther =
      csBigIntegerMPZparse(big2.ToByteArray());  // parse from little-endian

  bool r = (bThis > bOther);  // result
  return r;
}

bool BigInteger::operator<(const BigInteger& big2) const {
  if (this->IsError() || big2.IsError()) {
    return false;
  }

  mpz_class bThis =
      csBigIntegerMPZparse(this->ToByteArray());  // parse from little-endian
  mpz_class bOther =
      csBigIntegerMPZparse(big2.ToByteArray());  // parse from little-endian

  bool r = (bThis < bOther);  // result
  return r;
}

// ----------------- arithmetic ---------------------

BigInteger BigInteger::operator+(const BigInteger& big2) const {
  if (this->IsError() || big2.IsError()) return Error();

  mpz_class bThis =
      csBigIntegerMPZparse(this->ToByteArray());  // parse from little-endian
  mpz_class bOther =
      csBigIntegerMPZparse(big2.ToByteArray());  // parse from little-endian
  BigInteger r;                                  // result
  r._data = csBigIntegerGetBytesFromMPZ(bThis + bOther);  // get big-endian
  return r;
}

BigInteger BigInteger::operator-(const BigInteger& big2) const {
  if (this->IsError() || big2.IsError()) return Error();

  mpz_class bThis =
      csBigIntegerMPZparse(this->ToByteArray());  // parse from little-endian
  mpz_class bOther =
      csBigIntegerMPZparse(big2.ToByteArray());  // parse from little-endian
  BigInteger r;                                  // result
  r._data = csBigIntegerGetBytesFromMPZ(bThis - bOther);  // get big-endian
  return r;
}

BigInteger BigInteger::operator*(const BigInteger& big2) const {
  if (this->IsError() || big2.IsError()) return Error();

  mpz_class bThis =
      csBigIntegerMPZparse(this->ToByteArray());  // parse from little-endian
  mpz_class bOther =
      csBigIntegerMPZparse(big2.ToByteArray());  // parse from little-endian
  BigInteger r;                                  // result
  r._data = csBigIntegerGetBytesFromMPZ(bThis * bOther);  // get big-endian
  return r;
}

BigInteger BigInteger::operator/(const BigInteger& big2) const {
  if (this->IsError() || big2.IsError() || big2.IsZero()) return Error();
  mpz_class bThis =
      csBigIntegerMPZparse(this->ToByteArray());  // parse from little-endian
  mpz_class bOther =
      csBigIntegerMPZparse(big2.ToByteArray());  // parse from little-endian
  BigInteger r;                                  // result
  r._data = csBigIntegerGetBytesFromMPZ(bThis / bOther);  // get big-endian
  return r;
}

BigInteger BigInteger::operator%(const BigInteger& big2) const {
  if (this->IsError() || big2.IsError() || big2.IsZero()) return Error();

  mpz_class bThis =
      csBigIntegerMPZparse(this->ToByteArray());  // parse from little-endian
  mpz_class bOther =
      csBigIntegerMPZparse(big2.ToByteArray());  // parse from little-endian
  BigInteger r;                                  // result
  r._data = csBigIntegerGetBytesFromMPZ(bThis % bOther);  // get big-endian
  return r;
}

BigInteger BigInteger::operator<<(const BigInteger& big2) const {
  if (this->IsError() || big2.IsError()) return Error();
  if (big2 < Zero()) return (*this) >> -big2;

  mpz_class bThis =
      csBigIntegerMPZparse(this->ToByteArray());  // parse from little-endian
  BigInteger r;                                   // result
  r._data =
      csBigIntegerGetBytesFromMPZ(bThis << big2.toInt());  // get big-endian
  return r;
}

BigInteger BigInteger::operator>>(const BigInteger& big2) const {
  if (this->IsError() || big2.IsError()) return Error();
  if (big2 < Zero()) return (*this) << -big2;

  mpz_class bThis =
      csBigIntegerMPZparse(this->ToByteArray());  // parse from little-endian
  BigInteger r;                                   // result
  r._data =
      csBigIntegerGetBytesFromMPZ(bThis >> big2.toInt());  // get big-endian
  return r;
}

// =================== BEGIN MPZ AGAIN =======================

std::string BigInteger::toStringBase10() const {
  mpz_class bThis =
      csBigIntegerMPZparse(this->ToByteArray());  // parse from little-endian
  return bThis.get_str(10);
}

// assumes big >= 0
std::string csBigIntegerGetBitsFromNonNegativeMPZ(mpz_class big) {
  std::string sbin;
  while (big > 0) {
    mpz_class rest = (big % 2);
    sbin.insert(0, (rest.get_ui() == 0 ? std::string("0") : std::string("1")));
    big = big / 2;
  }
  return sbin;
}

cs_vbyte csBigIntegerGetBytesFromMPZ(mpz_class big) {
  // check if positive or negative
  if (big >= 0) {
    // -------------------
    // positive conversion
    // -------------------
    cs_vbyte v;
    while (big > 0) {
      mpz_class rest = (big % 256);
      v.push_back((cs_byte)rest.get_ui());
      big = big / 256;
    }

    // added in little-endian format (backwards)
    std::string leHex = Helper::toHexString(v);
    if (leHex.length() == 0) leHex = "00";
    // check if became negative
    if (Helper::checkNegativeBit(leHex)) {
      v.push_back(0);  // guarantee non-negative
    }

    // v is added backwards (little-endian), must reverse (to big-endian)
    reverse(v.begin(), v.end());
    if (v.size() == 0) v.push_back(0x00);
    // finished
    return v;
  } else {
    // -------------------
    // negative conversion
    // -------------------
    // turn into positive
    mpz_class x = big * (-1);
    // cout << "x positive " << x << endl;

    // ========================
    // perform two's complement
    // ========================
    // convert to binary
    cs_vbyte vx =
        csBigIntegerGetBytesFromMPZ(x);  // positive is easy to convert
    // cout << Helper::toHexString(vx) << endl;
    mpz_class bx(Helper::toHexString(vx), 16);
    // get binary representation
    std::string y = bx.get_str(2);
    // cout << "numbits: " << y.length() << endl;
    // cout << "ybits: " << y << endl;
    // cout << "dbits: " << csBigIntegerGetBitsFromNonNegativeMPZ(x) << endl;

    // extra padding for limit cases (avoid overflow)
    y.insert(0, "0");  // prepend

    // guarantee length must be at least 8, or add padding!
    while ((y.length() < 8) || (y.length() % 8 != 0)) {
      y.insert(0, "0");  // prepend
    }

    // invert bits
    std::string y2 = "";
    for (int i = 0; i < (int)y.length(); i++) y2 += (y[i] == '0' ? '1' : '0');
    // cout << "rbits: " << y2 << endl;

    // go back to bigint
    // BigInteger by3(y2, 2); // recursive behavior
    mpz_class by3(y2, 2);
    // sum 1
    mpz_class bby3 = by3 + 1;

    // cout << "(~y)+1: " << bby3 << endl;

    // convert to binary again
    std::string y4 = csBigIntegerGetBitsFromNonNegativeMPZ(bby3);
    // cout << "y4bits: " << y4 << endl;

    // padding
    while ((y4.length() < 8) || (y4.length() % 8 != 0)) {
      y4.insert(0, "0");  // prepend
    }

    // cout << "y4bits: " << y4 << endl;

    // get in bytes
    cs_vbyte v = Helper::BinToBytes(y4);

    // cout << "v: " << Helper::toHexString(v) << endl;

    // convert to little-endian
    reverse(v.begin(), v.end());  // to little-endian

    // will add extra ff to guarantee its negative, and simplify later (remove
    // extra ff)
    v.push_back(0xff);

    cs_vbyte vsimple = v;
    while ((vsimple.size() > 1) &&
           (vsimple.at(((int)vsimple.size()) - 1) == 0xff)) {
      vsimple.pop_back();
      std::string lehex = Helper::toHexString(vsimple);
      if (Helper::checkNegativeBit(lehex)) {
        // still negative! can keep removal
        v = vsimple;
      } else
        break;
    }

    // convert to big-endian
    reverse(v.begin(), v.end());  // to big-endian

    // finished
    return v;
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
mpz_class csBigIntegerMPZparse(cs_vbyte n) {
  // if (n.size() == 0)
  //    return mpz_class(0); // never invoked

  std::string s = Helper::toHexString(n);

  // verify if number is negative (most significant bit)
  if (Helper::checkNegativeBit(s)) {
    // is negative, must handle twos-complement
    mpz_class vint(Helper::revertHexString(s), 16);  // as big-endian again
    // get bitstring
    std::string rbitnum = csBigIntegerGetBitsFromNonNegativeMPZ(vint);
    // negate bits
    std::stringstream y2;
    for (int i = 0; i < (int)rbitnum.length(); i++)
      y2 << (rbitnum[i] == '0' ? '1' : '0');
    // to bigint again
    mpz_class by2(y2.str(), 2);
    // add one
    mpz_class by2add = by2 + 1;
    // get negative
    mpz_class finalnum = by2add * (-1);
    // ensure it's negative (TODO(igormcoelho): remove)
    assert(finalnum < 0);  // must be negative
    // finished
    return finalnum;
  } else {
    // positive is easy (in little-endian format)
    std::string sbig = Helper::revertHexString(s);
    // build bignum in big-endian
    return mpz_class(sbig, 16);  // big-endian again
  }
}

mpz_class csBigIntegerMPZparses(std::string n, int base) {
  if (base == 10) {
    // if (n.length() == 0)
    //    n = "0"; // not necessary
    return mpz_class(n, base);
  }

  // never used! internal function only
  // if (base == 2) {
  //   if (n.length() == 0)
  //      n = "0";
  //   return mpz_class(n, base);
  //}

  // never used! internal function only
  // if (base != 16) {
  //   cout << "UNSUPPORTED BASE! " << base << endl;
  //   exit(1);
  //}

  // zero padding
  while (n.length() < 2) n.insert(0, "0");

  // return bytearray initialized
  cs_vbyte vb;
  // prefix '0x' optional. input always big-endian
  if ((n[0] == '0') && (n[1] == 'x')) {
    // removing '0x'
    n = n.substr(2, n.length() - 2);
    vb = Helper::HexToBytes(n);

  } else {
    vb = Helper::HexToBytes(n);  // directly reading big-endian byte array
  }

  reverse(vb.begin(), vb.end());  // to little-endian

  // base 16
  return csBigIntegerMPZparse(vb);  // vb is little-endian byte array
}
