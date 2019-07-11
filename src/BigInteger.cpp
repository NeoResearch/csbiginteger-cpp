
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
using namespace csBigInteger;

// input is raw big-endian format (same as _data)
mpz_class
csBigIntegerMPZparse(vbyte n);

// string parse
mpz_class
csBigIntegerMPZparses(string n, int base);

/*
mpz_class
csBigIntegerToMPZFromBase10(string strDataBigDec)
{
   if (strDataBigDec.length() == 0)
      strDataBigDec = "0";
   mpz_class b(strDataBigDec, 10);
   return b;
}

mpz_class
csBigIntegerToMPZFromBase2(string strDataBigDec)
{
   if (strDataBigDec.length() == 0)
      strDataBigDec = "0";
   mpz_class b(strDataBigDec, 2);
   return b;
}
*/

string
csBigIntegerGetBitsFromNonNegativeMPZ(mpz_class big)
{
   if (big < 0) {
      cout << "NOT IMPLEMENTED FOR BIT NEGATIVE MPZ!" << endl;
      exit(1);
   }

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
   cout << " = = = > csBigIntegerGetBytesFromMPZ: big(10)=" << big.get_str(10) << endl;

   // positive conversion
   if (big >= 0) {
      vbyte v;
      cout << "NOW POSITIVE! (SHOULD NEVER CALL NEGATIVE!)" << endl;
      //int xx;
      //cin >> xx;
      while (big > 0) {
         mpz_class rest = (big % 256);
         v.push_back((byte)rest.get_ui());
         big = big / 256;
      }

      // added in little-endian format (backwards)
      string leHex = BigInteger::toHexString(v);
      if (leHex.length() == 0)
         leHex = "00";
      cout << "leHex: " << leHex;
      // check if became negative
      cout << endl;
      cout << "WILL CHECK NEGATIVE BIT!" << endl;
      if (BigInteger::checkNegativeBit(leHex)) {
         cout << "---> will add zero to avoid negative!" << endl;
         v.push_back(0); // guarantee non-negative
      }

      // v is added backwards (little-endian), must reverse (to big-endian)
      reverse(v.begin(), v.end());

      cout << "bytes (big-endian): " << BigInteger::toHexString(v) << endl;
      cout << "finished!" << endl
           << endl;
      //int x;
      //cin >> x;
      return v;
   } else {
      // negative conversion
      vbyte v;
      cout << endl
           << "NEGATIVE! LET THE BATTLE BEGIN! \\o/" << endl;
      //int xx;
      //cin >> xx;
      // from csBigInteger.js (could improve)
      // negative numbers
      //console.log("NEGATIVE: "+bigint);

      /*
		 // https://msdn.microsoft.com/en-us/library/system.numerics.biginteger(v=vs.110).aspx
		 The BigInteger structure assumes that negative values are stored by using two's complement representation. Because the BigInteger structure represents a numeric value with no fixed length, the BigInteger(Byte[]) constructor always interprets the most significant bit of the last byte in the array as a sign bit. To prevent the BigInteger(Byte[]) constructor from confusing the two's complement representation of a negative value with the sign and magnitude representation of a positive value, positive values in which the most significant bit of the last byte in the byte array would ordinarily be set should include an additional byte whose value is 0. For example, 0xC0 0xBD 0xF0 0xFF is the little-endian hexadecimal representation of either -1,000,000 or 4,293,967,296. Because the most significant bit of the last byte in this array is on, the value of the byte array would be interpreted by the BigInteger(Byte[]) constructor as -1,000,000. To instantiate a BigInteger whose value is positive, a byte array whose elements are 0xC0 0xBD 0xF0 0xFF 0x00 must be passed to the constructor.
		 */
      //x=-1000000; // must become (big endian) "f0bdc0" => little endian C0 BD F0  (careful with positive 4,293,967,296 that may become negative, need to be C0 BD F0 FF 00)
      // ASSERT (x < 0) !!! x==0 is problematic! equals to 256...
      //x=-1; // ff => 0x ff
      //x=-2; // fe => 0x fe
      //x=-127; // 81 => 0x 81
      //x=-255; // "ff01" => 0x 01 ff
      //x=-256; // "ff00" => 0x 00 ff
      //x=-257; // "feff" => 0x ff fe
      //x=-128; // "ff80" => 0x 80 ff
      // only for negative integers
      // var x = bigint.mul(new BN(-1)); // turn into positive
      mpz_class x = big * (-1); // turn into positive
                                //console.log("POSITIVE:" +x);
                                // ========================
                                // perform two's complement
                                // ========================
                                // convert to binary
      // var y = x.toString(2);
      vbyte vx = csBigIntegerGetBytesFromMPZ(x); // positive is easy to convert
      cout << "returned from csBigIntegerGetBytesFromMPZ (still in NEGATIVE part)" << endl;
      cout << "vx (big-endian):" << BigInteger::toHexString(vx) << endl;

      //vbyte vx_little = vx;
      //reverse(vx_little.begin(), vx_little.end()); // to little-endian
      //BigInteger bx(vx_little);
      mpz_class bx(BigInteger::toHexString(vx), 16);

      //cout << "bx:" << bx.ToString() << endl;
      cout << "bx:" << bx.get_str(16) << endl;
      //std::string y = bx.ToString(2);
      std::string y = bx.get_str(2);
      cout << "y: " << y << endl;
      //console.log("BINARY:" +y);
      //console.log("FIRST BINARY: "+y);
      // extra padding for limit cases (avoid overflow) // y = "0"+y;
      y.insert(0, "0"); // prepend

      //guarantee length must be at least 8, or add padding!
      while ((y.length() < 8) || (y.length() % 8 != 0)) {
         //console.log("ADDING PADDING 1!");
         //y = "0"+y;
         y.insert(0, "0"); // prepend
      }
      cout << "y: " << y << endl;
      //console.log("BINARY AFTER PADDING:" +y);
      // invert bits
      std::string y2 = "";
      for (int i = 0; i < y.length(); i++)
         y2 += (y[i] == '0' ? '1' : '0');
      //console.log("SECOND BINARY: "+y2);
      cout << "y2: " << y2 << endl;
      // go back to int
      //BigInteger by3(y2, 2); // recursive behavior
      mpz_class by3(y2, 2);
      //console.log("INT is "+y3);
      //cout << "by3: " << by3.toInt() << endl;
      cout << "by3: " << by3.get_ui() << endl;
      // sum 1
      mpz_class bby3 = by3 + 1;
      //console.log("INT is after sum "+y3);
      cout << "bby3: " << bby3.get_ui() << endl;

      // convert to binary again
      //std::string y4 = bby3.ToString(2);
      std::string y4 = csBigIntegerGetBitsFromNonNegativeMPZ(bby3);

      //guarantee length must be at least 8, or add padding!
      while (y4.length() < 8) {
         //console.log("ADDING PADDING!");
         //y4 = "0"+y4;
         y4.insert(0, "0"); // prepend
      }
      cout << "y4: " << y4 << endl;
      // convert to big-endian hex string
      //BigInteger by4(y4, 2);
      //cout << "by4: " << by4.toInt() << endl;
      //std::string y5 = by4.ToString(16);
      // convert to little-endian
      //return csBigInteger.revertHexString(y5);
      //v = BigInteger::HexToBytes(y5);
      v = BigInteger::BinToBytes(y4);
      cout << "final v:" << BigInteger::toHexString(v) << endl;

      return v;
   }
}

// nothing to initialize on empty constructor ('_data' is already empty)
BigInteger::BigInteger()
{
}

// input byte data in little-endian format
BigInteger::BigInteger(vbyte data)
  : _data(data)
{
   reverse(_data.begin(), _data.end()); // to little-endian
}

// default is base 10
// allows base 2
// if base 16, prefix '0x' indicates big-endian, otherwise is little-endian
BigInteger::BigInteger(string str, int base)
{
   mpz_class a = csBigIntegerMPZparses(str, base);
   cout << "PARSED str: " << str << " on base=" << base << ". Will convert MPZ to byte array." << endl;
   cout << "mpz (base): " << a.get_str(base) << endl;
   _data = csBigIntegerGetBytesFromMPZ(a);
}

BigInteger::BigInteger(int32 val)
{
   cout << "WILL WORK WITH int32 val=" << val << endl;
   mpz_class a = val;
   _data = csBigIntegerGetBytesFromMPZ(a);
   cout << "int32 " << val << " -> hexbig: " << BigInteger::toHexString(_data) << endl;
   //int x;
   //cin >> x;
}

BigInteger::BigInteger(int64 val)
{
   cout << "WILL WORK WITH int64 val=" << val << endl;
   mpz_class a = val;
   _data = csBigIntegerGetBytesFromMPZ(a);
   cout << "int64 " << val << " -> hexbig: " << BigInteger::toHexString(_data) << endl;
   //int x;
   //cin >> x;
}

int32
BigInteger::toInt() const
{
   cout << endl
        << " =========== toInt() =======" << endl;
   vbyte vb = this->ToByteArray(); // little-endian
   cout << "hex little: " << BigInteger::toHexString(vb) << endl;
   mpz_class a = csBigIntegerMPZparse(vb);
   cout << "===> toInt() ==> csBigIntegerMPZparse completed... will get ui" << endl;
   int32 i = a.get_ui(); // unsigned int
   if (a < 0)
      i *= -1;
   cout << "int is " << i << endl;
   return i;
}

int64
BigInteger::toLong() const
{
   cout << endl
        << " =========== toLong() =======" << endl;
   vbyte vb = this->ToByteArray(); // little-endian
   cout << "hex little: " << BigInteger::toHexString(vb) << endl;
   mpz_class a = csBigIntegerMPZparse(vb);
   cout << "===> toInt() ==> csBigIntegerMPZparse completed... will get ui" << endl;
   int64 i = a.get_si(); // signed long int
   cout << "long is " << i << endl;
   return i;
}

BigInteger
BigInteger::operator+(long l2)
{
   vbyte vb = this->ToByteArray(); // big-endian
   reverse(vb.begin(), vb.end());  // to little-endian
   mpz_class bThis = csBigIntegerMPZparse(vb);
   mpz_class bThisPlus = bThis + l2;
   return BigInteger(csBigIntegerGetBytesFromMPZ(bThisPlus));
}

// this method is very crazy... hope it works ;)
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
   // mpz_class b(strDataBigHex, 16);
   // return b;

   cout << "WILL PARSE BYTE ARRAY OF SIZE n=" << n.size() << endl;
   cout << "parsing little-endian hex: " << BigInteger::toHexString(n) << endl;
   if (n.size() == 0)
      return mpz_class(0);
   /*
	  // little-endian input array
		// [251, 0] -> "fb00" -> 251
		std::stringstream s;
		for(int i=0;i<n.size();i++) {
			std::string dig = BigInteger::toHexString(n[i]); // toString(16)
			if(dig.length==1)
				s << "0";
			s << dig;
		}
		return BigInteger::parse(s.str(), 16);
	} // end little-endian array
   */

   std::string s = BigInteger::toHexString(n); //.toString().toLowerCase().replace(/\W-/g, '');
   cout << " -------> parse s: " << s << endl;

   // base 10
   //if(base == 10) {
   //	return BigInteger(new BN(s.replace(/[^0-9-]/gi, ''), 10));
   //}

   // binary
   //if(base == 2) {
   //  return new csBigInteger(new BN(s.replace(/[^0-1]/gi, ''), 2));
   //}

   //s = s.replace(/[^0-9a-fx]/gi, '');
   // base 16
   //if(s.length < 2) // single hex digit
   //	return new csBigInteger(new BN(s, 16));

   // verify endianess (prefix '0x' enforces big-endian, otherwise is standard 'little-endian')
   // big-endian (must reverse to match C# standard little-endian)
   //if((s[0]=="0") && (s[1]=="x"))
   //{
   // big-endian
   //s = s.substr(2); // remove '0x
   // convert to little-endian
   //s = csBigInteger.revertHexString(s);
   //}

   // already little-endian s
   //s = BigInteger::revertHexString(s); // to little-endian

   // verify if number is negative (most significant bit)
   if (BigInteger::checkNegativeBit(s)) {
      cout << " ========> IS NEGATIVE lehex! s: " << s << endl;
      // is negative, must handle twos-complement
      mpz_class vint(BigInteger::revertHexString(s), 16);                // as big-endian again
      std::string rbitnum = csBigIntegerGetBitsFromNonNegativeMPZ(vint); //vint.ToString(2);
      cout << " ------> rbitnum: " << rbitnum << endl;
      // negate bits
      std::stringstream y2;
      for (int i = 0; i < rbitnum.length(); i++)
         y2 << (rbitnum[i] == '0' ? '1' : '0');
      cout << " ------> neg: " << y2.str() << endl;
      mpz_class by2(y2.str(), 2);
      mpz_class by2add = by2 + 1;
      mpz_class finalnum = by2add * (-1);
      //BigInteger finalnum =  new BN(y2, 2).add(new BN(1)).mul(new BN(-1));

      assert(finalnum < 0); // must be negative

      cout << " =======> finished parse negative mpz" << endl;
      return finalnum; //new csBigInteger(finalnum);
   } else {
      cout << " ========> IS POSITIVE lehex! s: " << s << endl;
      std::string sbig = BigInteger::revertHexString(s);
      cout << " -----> BIG ENDIAN TO MPZ: " << sbig << endl;
      // positive is easy
      //return new csBigInteger(new BN(csBigInteger.revertHexString(s), 16, 'be'));
      return mpz_class(sbig, 16); // big-endian again
   }

   // little-endian: BN(..., 'le') is currently with a known bug... using revertHexString instead
   //return new csBigInteger(new BN(csBigInteger.revertHexString(s), 16, 'be'));//csBigInteger.lehex2bigint(s));
}

mpz_class
csBigIntegerMPZparses(string n, int base)
{
   if (base == 10) {
      cout << " -----> directly converting to mpz base 10" << endl;
      if (n.length() == 0)
         n = "0";
      return mpz_class(n, base);
   }

   if (base == 2) {
      cout << " -----> directly converting to mpz base 10" << endl;
      if (n.length() == 0)
         n = "0";
      return mpz_class(n, base);
   }

   if (base != 16) {
      cout << "UNSUPPORTED BASE! " << base << endl;
      exit(1);
   }

   while (n.length() < 2)
      n.insert(0, "0"); // zero padding

   vbyte vb; // prefix '0x' indicates big-endian, otherwise is little-endian
   if ((n[0] == '0') && (n[1] == 'x')) {
      // removing '0x'
      n = n.substr(2, n.length() - 2);
      vb = BigInteger::HexToBytes(n);
      reverse(vb.begin(), vb.end()); // to little-endian
   } else
      vb = BigInteger::HexToBytes(n); // directly reading little-endian byte array

   // base 16
   return csBigIntegerMPZparse(vb); // vb is little-endian byte array
}
