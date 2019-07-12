#ifndef CS_BIGINTEGER_HELPER_HPP
#define CS_BIGINTEGER_HELPER_HPP

// system includes
#include <algorithm>
#include <iomanip>
#include <iostream> // todo: remove
#include <sstream>
#include <vector>

// c++ standard part
// ... none

#include "types.h"

// c++ types
typedef std::vector<byte> vbyte;

// original specification:
// https://referencesource.microsoft.com/#System.Numerics/System/Numerics/BigInteger.cs

// ======================================
// This class is intended to be immutable
// ======================================

namespace csbiginteger {
class Helper
{
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
      byte b = std::stol(y, nullptr, 16);       // parseInt(y,16)
      std::string bitnum = Helper::parseBin(b); //parseInt(y, 16).toString(2);
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

#endif // CS_BIGINTEGER_HELPER_HPP
