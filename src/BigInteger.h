#ifndef CS_BIGINTEGER_H
#define CS_BIGINTEGER_H

// system includes
#include <algorithm>
#include <iomanip>
#include <iostream> // todo: remove
#include <sstream>
#include <vector>

// c++ standard part
// ... none

typedef int int32;
typedef long int64;
typedef unsigned char byte;
typedef std::vector<byte> vbyte;

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
   // from neopt // helper
   static std::string toHexString(const vbyte& v)
   {
      std::stringstream ss;
      for (unsigned i = 0; i < v.size(); i++) // TODO: use foreach
         ss << std::setfill('0') << std::setw(2) << std::hex << (int)v[i];
      return ss.str();
   }

   // from neopt // helper
   static std::string toHexString(const byte& b)
   {
      return toHexString(vbyte(1, b));
   }

public:
   // object accessible helper method
   // hex string is returned on little-endian
   std::string toHexStr() const
   {
      vbyte data = this->_data;               //this->ToByteArray();        // big-endian
      std::reverse(data.begin(), data.end()); // to little-endian
      std::string s = BigInteger::toHexString(data);
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
         ss << "0x" << this->toHexStr();
         return ss.str();
      }

      if (base == 2) {
         std::stringstream ss;
         for (unsigned i = 0; i < _data.size(); i++)
            ss << parseBin(_data[i]); // byte to binary (TODO: verify if size is 8)
         return ss.str();
      }

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

private:
public: // helper
   // crazy method from csBigInteger.js
   // could be overly simplified
   // TODO: test (only indirectly tested now)
   static std::string revertHexString(std::string shex)
   {
      // if needs padding
      if (shex.length() % 2 == 1)
         shex.insert(0, "0"); // TODO: beware if that makes sense for negative... perhaps 'f' is better
      std::string hex = shex;

      std::string reverthex;
      for (int i = 0; i < (int)hex.length() - 1; i += 2) {
         reverthex.insert(0, hex.substr(i, 2));
      }
      return reverthex;
   }

   // crazy method from csBigInteger.js
   static bool checkNegativeBit(const std::string leHexStr)
   {
      //std::cout << "begin checkNegativeBit(" << leHexStr << ")" << std::endl;
      // check negative bit
      //std::string y = leHexStr.slice(leHexStr.length-2, leHexStr.length+2);
      std::string y = leHexStr.substr(leHexStr.length() - 2, 2);
      //console.log("base="+y);
      // detect negative values
      byte b = std::stol(y, nullptr, 16);           // parseInt(y,16)
      std::string bitnum = BigInteger::parseBin(b); //parseInt(y, 16).toString(2);
      //console.log("bitnum="+bitnum);
      // -1389293829382
      //std::cout << "end checkNegativeBit(" << leHexStr << ")" << std::endl;
      return (bitnum.length() == 8) && (bitnum[0] == '1');
   }

   // TODO: test
   static std::string parseBin(byte n)
   {
      std::string result;

      do
         result.push_back('0' + (n & 1));
      while (n >>= 1);

      reverse(result.begin(), result.end());
      return result;
   }

public: // helper
   // TODO: from neopt
   static vbyte HexToBytes(const std::string& hex)
   {
      // TODO: implement (begin 0x)
      //NEOPT_EXCEPTION("Not implemented yet: HexToBytes");
      vbyte bytes(hex.length() / 2);

      for (uint i = 0; i < hex.length(); i += 2) {
         std::string byteString = hex.substr(i, 2);
         byte b = (byte)strtol(byteString.c_str(), NULL, 16);
         bytes[i / 2] = b;
      }
      return bytes;
   }

   // binary format to bytes (must be 8-bit padded)
   static vbyte BinToBytes(const std::string& sbin)
   {
      vbyte bytes(sbin.length() / 8);

      for (uint i = 0; i < sbin.length(); i += 8) {
         std::string bitString = sbin.substr(i, 8);
         byte b = (byte)strtol(bitString.c_str(), NULL, 2);
         bytes[i / 8] = b;
      }
      return bytes;
   }
};
}

#endif // CS_BIG_INTEGER_H
