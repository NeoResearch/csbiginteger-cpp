#include "csBigIntegerLib.h"

// import big integer
#include "BigInteger.h"

//using namespace csbiginteger;

extern "C" int32
csbiginteger_init_empty(byte* vr, int sz_vr)
{
   csbiginteger::BigInteger big;
   // copy to memory
   bool r = big.CopyTo(vr, sz_vr);
   // check for errors
   return r ? big.Length() : 0;
}

// initialize big integer and return its size (in bytes). output vr must be pre-allocated
extern "C" int32
csbiginteger_init_i(int32 value, byte* vr, int sz_vr)
{
   csbiginteger::BigInteger big(value);
   // copy to memory
   bool r = big.CopyTo(vr, sz_vr);
   // check for errors
   return r ? big.Length() : 0;
}

// initialize big integer and return its size (in bytes). output vr must be pre-allocated
extern "C" int32
csbiginteger_init_l(int64 value, byte* vr, int sz_vr)
{
   csbiginteger::BigInteger big(value);
   // copy to memory
   bool r = big.CopyTo(vr, sz_vr);
   // check for errors
   return r ? big.Length() : 0;
}

// initialize big integer and return its size (in bytes). output vr must be pre-allocated
extern "C" int32
csbiginteger_init_s(char* value, int base, byte* vr, int sz_vr)
{
   csbiginteger::BigInteger big(std::string(value), base);
   // copy to memory
   bool r = big.CopyTo(vr, sz_vr);
   // check for errors
   return r ? big.Length() : 0;
}

// ================
// auxiliar methods
// ================

// ToString(base). input vb and output sr must be pre-allocated (return indicates failure, 'true' is fine)
extern "C" bool
csbiginteger_to_string(byte* vb, int sz_vb, int base, char* sr, int sz_sr)
{
   csbiginteger::BigInteger big(vbyte(vb, vb + sz_vb));
   std::string str = big.ToString(base);
   // check memory
   if (sz_sr < str.length())
      return false;
   // copy to string
   std::copy(str.begin(), str.end(), sr);
   return true;
}

extern "C" int
csbiginteger_to_int(byte* vb, int sz_vb)
{
   csbiginteger::BigInteger big(vbyte(vb, vb + sz_vb));
   int x = big.toInt();
   return x;
}

extern "C" long
csbiginteger_to_long(byte* vb, int sz_vb)
{
   csbiginteger::BigInteger big(vbyte(vb, vb + sz_vb));
   long x = big.toLong();
   return x;
}

// =======================
// csbiginteger operations
// =======================

// perform big1 == big2
extern "C" bool
csbiginteger_eq(byte* big1, int sz_big1, byte* big2, int sz_big2)
{
   csbiginteger::BigInteger b1(vbyte(big1, big1 + sz_big1));
   csbiginteger::BigInteger b2(vbyte(big2, big2 + sz_big2));
   return b1 == b2;
}

// perform big1 < big2
extern "C" bool
csbiginteger_lt(byte* big1, int sz_big1, byte* big2, int sz_big2)
{
   csbiginteger::BigInteger b1(vbyte(big1, big1 + sz_big1));
   csbiginteger::BigInteger b2(vbyte(big2, big2 + sz_big2));
   return b1 < b2;
}

// perform big1 > big2
extern "C" bool
csbiginteger_gt(byte* big1, int sz_big1, byte* big2, int sz_big2)
{
   csbiginteger::BigInteger b1(vbyte(big1, big1 + sz_big1));
   csbiginteger::BigInteger b2(vbyte(big2, big2 + sz_big2));
   return b1 > b2;
}

// perform big1 + big2 and return its size (in bytes). output vr must be pre-allocated
extern "C" int32
csbiginteger_add(byte* big1, int sz_big1, byte* big2, int sz_big2, byte* vr, int sz_vr)
{
   csbiginteger::BigInteger b1(vbyte(big1, big1 + sz_big1));
   csbiginteger::BigInteger b2(vbyte(big2, big2 + sz_big2));
   csbiginteger::BigInteger b3 = b1 + b2;
   if (b3 == csbiginteger::BigInteger::Error)
      return 0; // error
   if (!b3.CopyTo(vr, sz_vr))
      return 0; // error
   return b3.Length();
}

// perform big1 - big2 and return its size (in bytes). output vr must be pre-allocated
extern "C" int32
csbiginteger_sub(byte* big1, int sz_big1, byte* big2, int sz_big2, byte* vr, int sz_vr)
{
   csbiginteger::BigInteger b1(vbyte(big1, big1 + sz_big1));
   csbiginteger::BigInteger b2(vbyte(big2, big2 + sz_big2));
   csbiginteger::BigInteger b3 = b1 - b2;
   if (b3 == csbiginteger::BigInteger::Error)
      return 0; // error
   if (!b3.CopyTo(vr, sz_vr))
      return 0; // error
   return b3.Length();
}

// perform big1 * big2 and return its size (in bytes). output vr must be pre-allocated
extern "C" int32
csbiginteger_mul(byte* big1, int sz_big1, byte* big2, int sz_big2, byte* vr, int sz_vr)
{
   csbiginteger::BigInteger b1(vbyte(big1, big1 + sz_big1));
   csbiginteger::BigInteger b2(vbyte(big2, big2 + sz_big2));
   csbiginteger::BigInteger b3 = b1 * b2;
   if (b3 == csbiginteger::BigInteger::Error)
      return 0; // error
   if (!b3.CopyTo(vr, sz_vr))
      return 0; // error
   return b3.Length();
}

// perform big1 / big2 and return its size (in bytes). output vr must be pre-allocated
extern "C" int32
csbiginteger_div(byte* big1, int sz_big1, byte* big2, int sz_big2, byte* vr, int sz_vr)
{
   csbiginteger::BigInteger b1(vbyte(big1, big1 + sz_big1));
   csbiginteger::BigInteger b2(vbyte(big2, big2 + sz_big2));
   csbiginteger::BigInteger b3 = b1 / b2;
   if (b3 == csbiginteger::BigInteger::Error)
      return 0; // error
   if (!b3.CopyTo(vr, sz_vr))
      return 0; // error
   return b3.Length();
}

// perform big1 % big2 and return its size (in bytes). output vr must be pre-allocated
extern "C" int32
csbiginteger_mod(byte* big1, int sz_big1, byte* big2, int sz_big2, byte* vr, int sz_vr)
{
   csbiginteger::BigInteger b1(vbyte(big1, big1 + sz_big1));
   csbiginteger::BigInteger b2(vbyte(big2, big2 + sz_big2));
   csbiginteger::BigInteger b3 = b1 % b2;
   if (b3 == csbiginteger::BigInteger::Error)
      return 0; // error
   if (!b3.CopyTo(vr, sz_vr))
      return 0; // error
   return b3.Length();
}

// perform big1 << big2 and return its size (in bytes). output vr must be pre-allocated
extern "C" int32
csbiginteger_shl(byte* big1, int sz_big1, byte* big2, int sz_big2, byte* vr, int sz_vr)
{
   csbiginteger::BigInteger b1(vbyte(big1, big1 + sz_big1));
   csbiginteger::BigInteger b2(vbyte(big2, big2 + sz_big2));
   csbiginteger::BigInteger b3 = b1 << b2;
   if (b3 == csbiginteger::BigInteger::Error)
      return 0; // error
   if (!b3.CopyTo(vr, sz_vr))
      return 0; // error
   return b3.Length();
}

// perform big1 >> big2 and return its size (in bytes). output vr must be pre-allocated
extern "C" int32
csbiginteger_shr(byte* big1, int sz_big1, byte* big2, int sz_big2, byte* vr, int sz_vr)
{
   csbiginteger::BigInteger b1(vbyte(big1, big1 + sz_big1));
   csbiginteger::BigInteger b2(vbyte(big2, big2 + sz_big2));
   csbiginteger::BigInteger b3 = b1 >> b2;
   if (b3 == csbiginteger::BigInteger::Error)
      return 0; // error
   if (!b3.CopyTo(vr, sz_vr))
      return 0; // error
   return b3.Length();
}

// perform big ^ int32 and return its size (in bytes). output vr must be pre-allocated
extern "C" int32
csbiginteger_pow(byte* big, int sz_big, int exp, byte* vr, int sz_vr)
{
   csbiginteger::BigInteger b1(vbyte(big, big + sz_big));
   csbiginteger::BigInteger b3 = csbiginteger::BigInteger::Pow(b1, exp);
   if (b3 == csbiginteger::BigInteger::Error)
      return 0; // error
   if (!b3.CopyTo(vr, sz_vr))
      return 0; // error
   return b3.Length();
}