
#include <csbiginteger/BigInteger.h>

// system
// #include <iostream> // todo: remove

#include <assert.h>

#include <csbiginteger/HandBigInt.hpp>

//using namespace std;
using namespace csbiginteger;

// input is raw little-endian format
HandBigInt
csBigIntegerHANDparse(cs_vbyte n);

// string parse
HandBigInt
csBigIntegerHANDparses(std::string n, int base);

// get bitstring from mpz bignum non-negative object
std::string
csBigIntegerGetBitsFromNonNegativeHAND(HandBigInt big);

// get big-endian bytearray from mpz bignum (positive or negative)
cs_vbyte
csBigIntegerGetBytesFromHAND(HandBigInt big);

// ==================== END MPZ =======================


std::string
BigInteger::getEngine()
{
   return "HandBigInt";   
}


const BigInteger
BigInteger::error()
{
   BigInteger big;
   big._data = cs_vbyte(0); // empty array is error
   return big;
}

BigInteger
BigInteger::Pow(BigInteger value, int exponent)
{
   // according to C# spec, only non-negative int32 values accepted here
   if (exponent < 0)
      return BigInteger::Error();
   HandBigInt big1 = csBigIntegerHANDparse(value.ToByteArray());
   HandBigInt r;
   unsigned long _exp = exponent;
   r = HandBigInt::pow(big1, _exp);
   cs_vbyte vr = csBigIntegerGetBytesFromHAND(r);
   reverse(vr.begin(), vr.end()); // to little-endian
   return BigInteger(vr);
}

// default is base 10
// allows base 2
// if base 16, prefix '0x' indicates big-endian, otherwise is little-endian
BigInteger::BigInteger(std::string str, int base)
{
   //std::cerr << "======= BigInteger(str='" << str << "' base=" << base << ") =======" << std::endl;
   //
   HandBigInt a = csBigIntegerHANDparses(str, base);
   //std::cout << "big: '" << a << "'" << std::endl;
   _data = csBigIntegerGetBytesFromHAND(a);
   //std::cout << "_data: " << Helper::toHexString(_data) << std::endl;
   // ======== DEBUG CHECK
   /*
   if((base == 10) && (str != "-0")) {
      std::string check = this->ToString(10);
      std::cout << "ToString(): " << this->ToString() << std::endl;
      std::cout << "ToString(10): " << this->ToString(10) << std::endl;
      assert(str == check);
   }
   */
}

BigInteger::BigInteger(float val)
{
   HandBigInt a = val;

   _data = csBigIntegerGetBytesFromHAND(a);
}

cs_int32
BigInteger::toInt() const
{
   cs_vbyte vb = this->ToByteArray(); // little-endian
   HandBigInt a = csBigIntegerHANDparse(vb);
   //std::cout << "toInt a=" << a.toString() << std::endl;
   cs_int32 i = a.get_ui(); // unsigned int
   if (a < 0)
      i *= -1;
   return i;
}

cs_int64
BigInteger::toLong() const
{
   cs_vbyte vb = this->ToByteArray(); // little-endian
   HandBigInt a = csBigIntegerHANDparse(vb);
   cs_int64 i = a.get_si(); // signed long int
   return i;
}

bool
BigInteger::operator>(const BigInteger& big2) const
{
   if (this->IsError() || big2.IsError())
      return false;

   HandBigInt bThis = csBigIntegerHANDparse(this->ToByteArray()); // parse from little-endian
   HandBigInt bOther = csBigIntegerHANDparse(big2.ToByteArray()); // parse from little-endian

   bool r = (bThis > bOther); // result
   return r;
}

bool
BigInteger::operator<(const BigInteger& big2) const
{
   if (this->IsError() || big2.IsError()) {
      return false;
   }

   HandBigInt bThis = csBigIntegerHANDparse(this->ToByteArray()); // parse from little-endian
   HandBigInt bOther = csBigIntegerHANDparse(big2.ToByteArray()); // parse from little-endian

   bool r = (bThis < bOther); // result
   return r;
}

// ----------------- arithmetic ---------------------

BigInteger&
BigInteger::operator+=(int iother)
{
   BigInteger other{ iother };

   *this = *this + other;
   return *this;
}

BigInteger
BigInteger::operator+(const BigInteger& big2) const
{
   if (this->IsError() || big2.IsError())
      return Error();

   HandBigInt bThis = csBigIntegerHANDparse(this->ToByteArray()); // parse from little-endian
   HandBigInt bOther = csBigIntegerHANDparse(big2.ToByteArray()); // parse from little-endian
   BigInteger r;                                                  // result
   r._data = csBigIntegerGetBytesFromHAND(bThis + bOther);        // get big-endian
   return r;
}

BigInteger
BigInteger::operator-(const BigInteger& big2) const
{
   if (this->IsError() || big2.IsError())
      return Error();

   HandBigInt bThis = csBigIntegerHANDparse(this->ToByteArray()); // parse from little-endian
   HandBigInt bOther = csBigIntegerHANDparse(big2.ToByteArray()); // parse from little-endian
   BigInteger r;                                                  // result
   r._data = csBigIntegerGetBytesFromHAND(bThis - bOther);        // get big-endian
   return r;
}

BigInteger
BigInteger::operator*(const BigInteger& big2) const
{
   if (this->IsError() || big2.IsError())
      return Error();

   HandBigInt bThis = csBigIntegerHANDparse(this->ToByteArray()); // parse from little-endian
   HandBigInt bOther = csBigIntegerHANDparse(big2.ToByteArray()); // parse from little-endian
   BigInteger r;                                                  // result
   r._data = csBigIntegerGetBytesFromHAND(bThis * bOther);        // get big-endian
   return r;
}

BigInteger
BigInteger::operator/(const BigInteger& big2) const
{
   if (this->IsError() || big2.IsError() || big2.IsZero())
      return Error();
   HandBigInt bThis = csBigIntegerHANDparse(this->ToByteArray()); // parse from little-endian
   HandBigInt bOther = csBigIntegerHANDparse(big2.ToByteArray()); // parse from little-endian
   BigInteger r;                                                  // result
   r._data = csBigIntegerGetBytesFromHAND(bThis / bOther);        // get big-endian
   return r;
}

BigInteger
BigInteger::operator%(const BigInteger& big2) const
{
   if (this->IsError() || big2.IsError() || big2.IsZero())
      return Error();

   HandBigInt bThis = csBigIntegerHANDparse(this->ToByteArray()); // parse from little-endian
   HandBigInt bOther = csBigIntegerHANDparse(big2.ToByteArray()); // parse from little-endian
   BigInteger r;                                                  // result
   r._data = csBigIntegerGetBytesFromHAND(bThis % bOther);        // get big-endian
   return r;
}

BigInteger
BigInteger::operator<<(const BigInteger& big2) const
{
   if (this->IsError() || big2.IsError())
      return Error();
   if (big2 < Zero())
      return (*this) >> -big2;

   HandBigInt bThis = csBigIntegerHANDparse(this->ToByteArray()); // parse from little-endian
   BigInteger r;                                                  // result
   r._data = csBigIntegerGetBytesFromHAND(bThis << big2.toInt()); // get big-endian
   return r;
}

BigInteger
BigInteger::operator>>(const BigInteger& big2) const
{
   if (this->IsError() || big2.IsError())
      return Error();
   if (big2 < Zero())
      return (*this) << -big2;

   HandBigInt bThis = csBigIntegerHANDparse(this->ToByteArray()); // parse from little-endian
   BigInteger r;                                                  // result
   r._data = csBigIntegerGetBytesFromHAND(bThis >> big2.toInt()); // get big-endian
   return r;
}

// =================== BEGIN MPZ AGAIN =======================

std::string
BigInteger::toStringBase10() const
{
   //std::cout << "toStringBase10()" << std::endl;
   HandBigInt bThis = csBigIntegerHANDparse(this->ToByteArray()); // parse from little-endian
   //std::cout << "base10 -> " << bThis << std::endl;
   return bThis.get_str(10);
}

// assumes big >= 0
std::string
csBigIntegerGetBitsFromNonNegativeHAND(HandBigInt big)
{
   // TODO: remove!
   assert(big >= 0);

   std::string sbin;
   while (big > 0) {
      HandBigInt rest = (big % 2);
      sbin.insert(0, (rest.get_ui() == 0 ? std::string("0") : std::string("1")));
      big = big / 2;
   }
   return sbin;
}

cs_vbyte
csBigIntegerGetBytesFromHAND(HandBigInt big)
{
   //std::cerr << "------ csBigIntegerGetBytesFromHAND: big -> " << big << std::endl;
   //
   // check if positive or negative
   if (big >= 0) {
      // -------------------
      // positive conversion
      // -------------------
      cs_vbyte v;
      while (big > 0) {
         //std::cout << "big=" << big << std::endl;
         HandBigInt rest = (big % 256);
         //std::cout << "rest=" << rest << std::endl;
         v.push_back((cs_byte)rest.get_ui());
         //std::cout << "REST=" << rest.get_ui() << std::endl;
         big = big / 256;
      }

      // added in little-endian format (backwards)
      std::string leHex = Helper::toHexString(v);
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
      //std::cout << " ------ finished csBigIntegerGetBytesFromHAND" << std::endl;
      //
      return v;
   } else {
      //std::cout << "IS NEGATIVE!" << std::endl;
      // -------------------
      // negative conversion
      // -------------------
      // turn into positive
      HandBigInt x = big * (-1);
      //std::cout << "x positive " << x << std::endl;

      // ========================
      // perform two's complement
      // ========================
      // convert to binary
      cs_vbyte vx = csBigIntegerGetBytesFromHAND(x); // positive is easy to convert
      //std::cout << Helper::toHexString(vx) << std::endl;
      //
      //HandBigInt bx(Helper::toHexString(vx), 16);
      HandBigInt bx = HandBigInt::fromUnsignedHex(Helper::toHexString(vx));
      //std::cout << "bx:" << bx.toString() << std::endl;
      //

      // get binary representation
      std::string y = bx.get_str(2);
      //std::cout << "numbits: " << y.length() << std::endl;
      //std::cout << "ybits: " << y << std::endl;
      //cout << "dbits: " << csBigIntegerGetBitsFromNonNegativeHAND(x) << endl;

      // extra padding for limit cases (avoid overflow)
      y.insert(0, "0"); // prepend

      //guarantee length must be at least 8, or add padding!
      while ((y.length() < 8) || (y.length() % 8 != 0)) {
         y.insert(0, "0"); // prepend
      }

      // invert bits
      std::string y2 = "";
      for (int i = 0; i < (int)y.length(); i++)
         y2 += (y[i] == '0' ? '1' : '0');
      //cout << "rbits: " << y2 << endl;

      // go back to bigint
      //BigInteger by3(y2, 2); // recursive behavior
      //
      //HandBigInt by3(y2, 2);
      HandBigInt by3 = HandBigInt::fromUnsignedBin(y2);
      //

      // sum 1
      HandBigInt bby3 = by3 + 1;

      //cout << "(~y)+1: " << bby3 << endl;

      // convert to binary again
      std::string y4 = csBigIntegerGetBitsFromNonNegativeHAND(bby3);
      //cout << "y4bits: " << y4 << endl;

      // padding
      while ((y4.length() < 8) || (y4.length() % 8 != 0)) {
         y4.insert(0, "0"); // prepend
      }

      //cout << "y4bits: " << y4 << endl;

      // get in bytes
      cs_vbyte v = Helper::BinToBytes(y4);

      //cout << "v: " << Helper::toHexString(v) << endl;

      // convert to little-endian
      reverse(v.begin(), v.end()); // to little-endian

      // will add extra ff to guarantee its negative, and simplify later (remove extra ff)
      v.push_back(0xff);

      cs_vbyte vsimple = v;
      while ((vsimple.size() > 1) && (vsimple.at(((int)vsimple.size()) - 1) == 0xff)) {
         vsimple.pop_back();
         std::string lehex = Helper::toHexString(vsimple);
         if (Helper::checkNegativeBit(lehex)) {
            // still negative! can keep removal
            v = vsimple;
         } else
            break;
      }

      // convert to big-endian
      reverse(v.begin(), v.end()); // to big-endian

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
HandBigInt
csBigIntegerHANDparse(cs_vbyte n)
{
   //std::cerr << "csBigIntegerHANDparse(" << Helper::toHexString(n) << ")" << std::endl;
   //
   //if (n.size() == 0)
   //   return HandBigInt(0); // never invoked

   std::string s = Helper::toHexString(n);
   //std::cout << "  ---> s => 0x" << s << std::endl;

   // verify if number is negative (most significant bit)
   if (Helper::checkNegativeBit(s)) {
      //std::cout << "csBigIntegerHANDparse is negative!" << std::endl;
      // is negative, must handle twos-complement
      //
      //HandBigInt vint(Helper::revertHexString(s), 16); // as big-endian again
      HandBigInt vint = HandBigInt::fromUnsignedHex(Helper::revertHexString(s));
      //std::cout << "csBigIntegerHANDparse vint=" << vint.toString() << std::endl;
      //
      //
      // get bitstring
      std::string rbitnum = csBigIntegerGetBitsFromNonNegativeHAND(vint);
      //std::cout << "rbitnum = " << rbitnum << std::endl;
      // negate bits
      std::stringstream y2;
      for (int i = 0; i < (int)rbitnum.length(); i++)
         y2 << (rbitnum[i] == '0' ? '1' : '0');
      // to bigint again
      //
      //HandBigInt by2(y2.str(), 2);
      HandBigInt by2 = HandBigInt::fromUnsignedBin(y2.str());
      //std::cout << "by2 = " << by2.toString() << std::endl;
      //
      // add one
      HandBigInt by2add = by2 + 1;
      //std::cout << "by2add = " << by2add.toString() << std::endl;
      // get negative
      HandBigInt finalnum = by2add * (-1);
      //std::cout << "finalnum = " << finalnum.toString() << std::endl;
      // ensure it's negative (TODO: remove)
      assert(finalnum < 0); // must be negative
      // finished
      return finalnum;
   } else {
      // positive is easy (in little-endian format)
      std::string sbig = Helper::revertHexString(s);
      //
      // build bignum in big-endian
      //return HandBigInt(sbig, 16); // big-endian again
      return HandBigInt::fromUnsignedHex(sbig); // big-endian again
   }
}

HandBigInt
csBigIntegerHANDparses(std::string n, int base)
{
   //std::cerr << "   --> csBigIntegerHANDparses(n='" << n << "' base =" << base << ")" << std::endl;
   //
   if (base == 10) {
      //if (n.length() == 0)
      //   n = "0"; // not necessary
      HandBigInt h(n);
      //std::cout << " --> csBigIntegerHANDparses ---> h=" << h.toString() << std::endl;
      return h;
   }

   // never used! internal function only
   //if (base == 2) {
   //   if (n.length() == 0)
   //      n = "0";
   //   return HandBigInt(n, base);
   //}

   // never used! internal function only
   //if (base != 16) {
   //   cout << "UNSUPPORTED BASE! " << base << endl;
   //   exit(1);
   //}

   // zero padding
   while (n.length() < 2)
      n.insert(0, "0");

   // return bytearray initialized
   cs_vbyte vb;
   // prefix '0x' optional. input always big-endian
   if ((n[0] == '0') && (n[1] == 'x')) {
      // removing '0x'
      n = n.substr(2, n.length() - 2);
      vb = Helper::HexToBytes(n);

   } else {
      vb = Helper::HexToBytes(n); // directly reading big-endian byte array
   }

   reverse(vb.begin(), vb.end()); // to little-endian

   // base 16
   return csBigIntegerHANDparse(vb); // vb is little-endian byte array
}
