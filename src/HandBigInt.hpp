// Hand Big Integer (big calculations done by hand)
// Author: Igor Machado Coelho
// Copyleft 2020 - MIT License

#ifndef HANDBIGINT_HPP
#define HANDBIGINT_HPP

#include <iostream>

#include <assert.h>

// TODO: make this independent from csbiginteger helpers and types

//#include "Helper.hpp"
/*
#include "types.h"
using cs_byte = csbiginteger::cs_byte;
using cs_vbyte = csbiginteger::cs_vbyte;
using Helper = csbiginteger::Helper;
*/
namespace csbiginteger_types {

using cs_byte = unsigned char;
static_assert(sizeof(cs_byte) == 1);

using cs_int32 = int;
static_assert(sizeof(cs_int32) == 4);

using cs_uint32 = unsigned int;
static_assert(sizeof(cs_uint32) == 4);

using cs_int64 = long long;
static_assert(sizeof(cs_int64) == 8);

using cs_uint64 = unsigned long long;
static_assert(sizeof(cs_uint64) == 8);

} // namespace csbiginteger_types

using cs_byte = csbiginteger_types::cs_byte;
using cs_vbyte = std::vector<csbiginteger::cs_byte>;
using cs_uint32 = csbiginteger_types::cs_uint32;
using cs_uint64 = csbiginteger_types::cs_uint64;
//using cs_vbyte = csbiginteger_types::cs_vbyte;
//using Helper = csbiginteger_types::Helper;

class HandHelper
{
public:
   static cs_vbyte HexToBytes(const std::string& hex)
   {
      // TODO: implement (begin 0x)
      //NEOPT_EXCEPTION("Not implemented yet: HexToBytes");
      cs_vbyte bytes(hex.length() / 2);

      for (cs_uint32 i = 0; i < hex.length(); i += 2) {
         std::string byteString = hex.substr(i, 2);
         cs_byte b = (cs_byte)strtol(byteString.c_str(), NULL, 16);
         bytes[i / 2] = b;
      }
      return bytes;
   }
};

class HandBigInt
{
public:
   // the internals of HandBigInt are meant to be simple
   std::string sdec; // decimals in reversed string format
   int sign;
   bool error;

   // must implement this
   HandBigInt()
   {
      //sdec="0"; // TODO: may require this or leave to 'fix'
      sdec = "";
      sign = 1;
      error = false;
   }

   // must implement this
   HandBigInt(float f)
     : HandBigInt(std::to_string(f))
   {
      /*
      std::cerr << "TODO: check if float is not given in scientific notation" << std::endl;
      std::string str = std::to_string(f);
      int _sign = (str[0] == '-' ? -1 : 1);
      sdec = (_sign == -1 ? str.substr(1) : str);
      std::reverse(str.begin(), str.end());
      this->sdec = str;
      this->sign = _sign;
      this->fix(_sign);
      */
   }

   //this is optional (good for basic testing)
   HandBigInt(int i)
     : HandBigInt(std::to_string(i))
   {
      /*
      std::cout << "HandBigInt(" << i << ")" << std::endl;
      std::string str = std::to_string(i);
      int _sign = (str[0] == '-' ? -1 : 1);
      sdec = (_sign == -1 ? str.substr(1) : str);
      std::reverse(str.begin(), str.end());
      this->sdec = str;
      this->sign = _sign;
      this->fix(_sign);
      std::cout << "sdec -> '" << sdec << "' sign=" << sign << std::endl;
      */
   }

   // build from hex string in Big Endian
   static HandBigInt fromUnsignedHex(std::string str)
   {
      //std::cout << " =============  fromUnsignedHex BUILD base16: " << str << std::endl;
      //std::cout << "WARNING: this is always positive and Big Endian!" << std::endl;

      // removing '0x'
      if ((str.length() >= 2) && (str[0] == '0') && (str[1] == 'x'))
         str = str.substr(2, str.length() - 2);

      // zero padding
      while (str.length() % 2 == 1)
         str.insert(0, "0");

      // return bytearray initialized (in Big Endian)
      //cs_vbyte vb = Helper::HexToBytes(str);
      cs_vbyte vb = HandHelper::HexToBytes(str);
      //std::cout << " -------> fromUnsignedHex -> " << Helper::toHexString(vb) << std::endl;

      // build number byte by byte
      HandBigInt big(0);
      for (unsigned i = 0; i < vb.size(); i++) {
         //std::cout << big.toString();
         big = big * 256 + vb[i];
         //std::cout << "*256 + " << (int)vb[i] << " = " << big << std::endl;
      }

      //std::cout << "=====> fromUnsignedHex FINAL 16  in decimal = " << big.toString() << std::endl;

      //this->sign = 1; // positive
      //this->sdec = big.sdec; // get internal
      big.sign = 1;
      return big;
   }

   // build from binary string
   static HandBigInt fromUnsignedBin(std::string str)
   {
      //std::cout << " ============= BUILD base2: " << str << std::endl;
      //std::cout << "WARNING: this is always positive and Big Endian!" << std::endl;

      // removing '0b'
      if ((str.length() >= 2) && (str[0] == '0') && (str[1] == 'b'))
         str = str.substr(2, str.length() - 2);

      // build number bit by bit
      HandBigInt big(0);
      for (unsigned i = 0; i < str.length(); i++) {
         big = big * 2 + (str[i] - '0');
      }

      //std::cout << "=====> FINAL 2  in decimal = " << big.toString() << std::endl;

      big.sign = 1;
      return big;
   }

   // must implement this
   // we only accept base 10 here, for other bases, use the helpers above
   HandBigInt(std::string str)
   {
      //std::cout << "HandBigInt('" << str << "')" << std::endl;
      error = false;
      // shortcuts to build zero, one, 256, minus one
      if (str == "0") {
         //std::cout << "BUILD DEFAULT ZERO (base 10): " << str << std::endl;
         this->sdec = "0";
         this->sign = 1;
      } else if (str == "1") {
         //std::cout << "BUILD DEFAULT ONE (base 10): " << str << std::endl;
         this->sdec = "1";
         this->sign = 1;
      } else if (str == "2") {
         //std::cout << "BUILD DEFAULT TWO (base 10): " << str << std::endl;
         this->sdec = "2";
         this->sign = 1;
      } else if (str == "10") {
         //std::cout << "BUILD DEFAULT TEN (base 10): " << str << std::endl;
         this->sdec = "01";
         this->sign = 1;
      } else if (str == "256") {
         //std::cout << "BUILD DEFAULT 256 (base 10): " << str << std::endl;
         this->sdec = "652";
         this->sign = 1;
      }
      //else if (base == 10) {
      else {
         //std::cout << "BUILD base10: " << str << std::endl;
         //
         //sdec = str; // CANNOT DO THIS DIRECTLY, MUST REVERSE AND FIX!
         int _sign = (str[0] == '-' ? -1 : 1);
         this->sdec = (_sign == -1 ? str.substr(1) : str);
         this->sign = _sign;
         std::reverse(this->sdec.begin(), this->sdec.end());
         this->fix(_sign);
         //std::cout << "BUILD finished after reverse and fix: '" << this->sdec << "'" << std::endl;
      }
      //std::cout << "finished constructor: sdec = '" << sdec << "' sign=" << sign << std::endl << std::endl;
   }

   ~HandBigInt()
   {
   }

   std::string toString() const
   {
      std::string str = this->sdec;
      std::reverse(str.begin(), str.end());
      if (this->sign == -1)
         str.insert(0, "-");
      return str;
   }

   bool isZero() const
   {
      return (this->sdec.size() == 1) && (this->sdec[0] == '0');
   }

   bool isError() const
   {
      return error;
   }

   // ================
   // returns inverted version of this big integer
   HandBigInt neg()
   {
      HandBigInt copy = *this;
      // TODO: check if we need to fix before copy
      copy.sign *= -1;
      return copy;
   }

   // workaround to fix current number with new sign, and erase extra zeroes
   // warning: this will fix/change current number and return copy
   HandBigInt fix(int _sign)
   {
      //std::cerr << "FIX()" << std::endl;
      for (int i = sdec.size() - 1; i > 0 && sdec[i] == '0'; i--)
         sdec.erase(sdec.begin() + i); // get rid of last zeroes (useless)
      // update sign (check if only one zero remained)
      this->sign = (sdec.size() == 1 && sdec[0] == '0' ? 1 : _sign);
      // returns copy of myself (fixed)
      return *this;
   }

   // ================

   static HandBigInt pow(HandBigInt base, unsigned int exp)
   {
      HandBigInt num = 1;
      for (int i = 0; i < exp; i++)
         num = num * base;
      return num;
   }

   // get as string in specific base
   std::string get_str(int base = 10)
   {
      if (base == 10) {
         /*
         std::cout << "base10 sdec=" << this->sdec << std::endl;
         std::string str = this->sdec;
         std::reverse(str.begin(), str.end());
         return str;
         */
         // re-use toString() implementation
         return toString();
      } else if (base == 16) {
         std::cerr << "TODO: get_str implement base 16 in Hand" << std::endl;
         assert(false);
      } else {
         //std::cerr << "get_str BASE " << base << std::endl;
         std::string sbin;
         HandBigInt copy = *this;
         while (copy > 0) {
            HandBigInt binDigit = copy % 2;
            //sbin += binDigit.toString()[0];
            sbin.insert(sbin.begin(), binDigit.toString()[0]);
            copy = copy / 2;
         }
         // give in multiple of 8's (don't know why exactly...)
         //while(sbin.length()%8 != 0)
         //   sbin.insert(sbin.begin(), '0');
         return sbin;
      }
      // default
      return "";
   }

   // unsigned int (uint32)
   unsigned int get_ui()
   {
      std::string str = this->sdec;
      std::reverse(str.begin(), str.end());
      // this expects UNSIGNED int... ignore sign
      //if (this->sign == -1)
      //   str.insert(0, "-");
      int x = atoi(str.c_str());
      return x;
   }

   // signed long (int64)
   long int get_si()
   {
      std::string str = this->sdec;
      std::reverse(str.begin(), str.end());
      if (this->sign == -1)
         str.insert(0, "-");
      char* pEnd;
      long int x = strtol(str.c_str(), &pEnd, 10);
      return x;
   }

   HandBigInt operator+(const HandBigInt& other)
   {
      //std::cout << "operator+(me=" << *this << " other=" << other << ")" << std::endl;
      // perform copy of myself (TODO: do we really need this?)
      HandBigInt copy = *this;

      // if signs are different, it's subtraction: we need to call operator-
      if (copy.sign != other.sign) {
         HandBigInt other2 = other; // copy to invert
         return copy - other2.neg();
      }

      // result to return
      HandBigInt r;

      int c = 0; // value to carry
      for (int i = 0; i < std::max(sdec.size(), other.sdec.size()) || c > 0; i++) {
         // add on 'c' from 'copy' and 'other'
         if (i < copy.sdec.size())
            c += copy.sdec[i] - '0';
         if (i < other.sdec.size())
            c += other.sdec[i] - '0';

         // put carry on result 'r'
         r.sdec += (c % 10 + '0');
         // leave rest on 'c' to carry next
         c /= 10;
      }

      return r.fix(this->sign);
   }

   HandBigInt operator-(const HandBigInt& other)
   {
      //std::cout << "operator-(me=" << *this << " other=" << other << ")" << std::endl;
      HandBigInt copy = *this;

      HandBigInt other2 = other;
      // if sign is different, operation is addition
      if (copy.sign != other2.sign) {
         return copy + other2.neg();
      }

      // store old sign
      int _sign = copy.sign;
      // set all positive
      copy.sign = other2.sign = 1;
      // TODO: assume other is positive
      //copy.sign = 1;

      // invoke operator<
      if (copy < other2)
         return ((other2 - copy).neg()).fix(-_sign);

      //std::cout << "operator- general computation copy.sdec='" << sdec << "' other2.sdec='" << other2.sdec << "'" << std::endl;
      // first operand must be greater than second
      HandBigInt r;
      //
      int b = 0; // for borrow operations
      for (unsigned i = 0; i < sdec.size(); i++) {
         b += (copy.sdec[i] - '0');

         if (i < other2.sdec.size())
            b -= other2.sdec[i] - '0';

         // add char into sdec sequence
         if (b >= 0)
            r.sdec += b + '0';
         else
            r.sdec += b + '0' + 10;

         b = (b >= 0 ? 0 : -1);
      }

      //std::cout << "operator- general computation = " << *this << std::endl;
      return r.fix(_sign);
   }

   HandBigInt operator*(const HandBigInt& other)
   {
      HandBigInt r("0");
      HandBigInt other2 = other;

      for (int i = 0; i < sdec.size(); i++) {
         int v = sdec[i] - '0';
         while (v--) {
            // apply several additions
            r = r + other2;
         }

         other2.sdec.insert(other2.sdec.begin(), '0');
      }

      return r.fix(this->sign * other2.sign);
   }

   HandBigInt operator/(const HandBigInt& other)
   {
      //std::cout << "operator/(" << *this << " , " << other << ")" << std::endl;

      HandBigInt other2 = other;

      if (other2.isZero()) {
         //other2.sdec[0] /= (other2.sdec[0] - '0');
         std::cerr << "DIVISION BY ZERO! TODO: use 'error' flag" << std::endl;
         assert(false);
      }

      HandBigInt r;

      // fill result with zeroes
      for (unsigned i = 0; i < sdec.size(); i++)
         r.sdec += "0";

      // get final sign
      int _sign = this->sign * other2.sign;

      // make positive
      other2.sign = 1;

      HandBigInt aux{ 0 }; // AUX is zero!
      for (int i = ((int)sdec.size()) - 1; i >= 0; i--) {
         //aux.sdec.insert(aux.sdec.begin(), '0'); // multiply by 10
         aux = aux * 10;
         HandBigInt num(sdec.substr(i, 1));
         //aux = aux + sdec.substr(i, 1);
         aux = aux + num;
         //std::cout << "aux = '" << aux.sdec << "'" << std::endl;

         while (!(aux < other2)) {
            aux = aux - other2;
            r.sdec[i]++;
         }
      }

      return r.fix(_sign);
   }

   HandBigInt operator%(const HandBigInt& other)
   {
      //std::cout << "operator%(" << *this << " , " << other << ")" << std::endl;

      HandBigInt other2 = other;

      //if (other2.sdec.size() == 1 && other2.sdec[0] == '0')
      //   other2.sdec[0] /= (other2.sdec[0] - '0');
      if (other2.isZero()) {
         //other2.sdec[0] /= (other2.sdec[0] - '0');
         std::cerr << "DIVISION (MOD) BY ZERO! TODO: use 'error' flag" << std::endl;
         assert(false);
      }

      HandBigInt r("0");

      other2.sign = 1;

      for (int i = sdec.size() - 1; i >= 0; i--) {
         r.sdec.insert(r.sdec.begin(), '0');

         r = r + sdec.substr(i, 1);

         while (!(r < other2))
            r = r - other2;
      }

      return r.fix(this->sign);
   }

   friend std::ostream& operator<<(std::ostream& os, const HandBigInt& me)
   {
      os << me.toString();
      return os;
   }

   // =====================

   bool operator==(const HandBigInt& other) const
   {
      // TODO: shall we require fix?
      return (this->sign == other.sign) && (this->sdec == other.sdec);
   }

   bool operator<(const HandBigInt& other)
   {
      //std::cerr << "HandBigInt operator<" << std::endl;

      // if signs are different, check which one is greater
      if (sign != other.sign)
         return sign < other.sign;

      // signs are the same

      // TODO: assuming both numbers are fixed (no extra zero allowed here!)

      // if sizes are different, check which one is greater
      if (sdec.size() != other.sdec.size()) {
         if (sign == 1) // positive
            return sdec.size() < other.sdec.size();
         else
            return sdec.size() > other.sdec.size();
      }

      // compare big end (last part) first ('sdec' is Little Endian Decimal, or something like that)
      for (int i = sdec.size() - 1; i >= 0; i--)
         if (sdec[i] != other.sdec[i]) {
            if (sign == 1) // positive
               return sdec[i] < other.sdec[i];
            else
               return sdec[i] > other.sdec[i];
         }

      // default is false (do we actually need this?)
      return false;
   }

   // use operator== and operator< (do we have spaceship <=> already?)
   bool operator<=(const HandBigInt& other)
   {
      return (*this < other || *this == other);
   }

   // use operator== and operator< (do we have spaceship <=> already?)
   bool operator>(const HandBigInt& other)
   {
      //std::cerr << "HandBigInt operator>" << std::endl;
      return not(*this < other) && not(*this == other);
   }

   // use operator== and operator> (do we have spaceship <=> already?)
   bool operator>=(const HandBigInt& other)
   {
      return (*this > other || *this == other);
   }

   // =====================

   // shift left (multiply by two)
   HandBigInt operator<<(int32_t big)
   {
      if (big < 0)
         return this->operator>>(-big);
      //
      for (int i = 0; i < big; i++)
         (*this) = (*this) * 2;
      return *this;
   }

   // shift right (divide by two)
   HandBigInt operator>>(int32_t big)
   {
      if (big < 0)
         return this->operator<<(-big);
      //
      for (int i = 0; i < big; i++)
         (*this) = (*this) / 2;
      return *this;
   }
};

/*
HandBigInt HandBigInt::Zero = HandBigInt(0);
HandBigInt HandBigInt::One = HandBigInt(1);
HandBigInt HandBigInt::MinusOne = HandBigInt(-1);
*/

#endif // HANDBIGINT_HPP