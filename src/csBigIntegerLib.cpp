#include "csBigIntegerLib.h"

// import big integer
#include "BigInteger.h"

//using namespace csbiginteger;

using cs_byte = csbiginteger::cs_byte;
using cs_int32 = csbiginteger::cs_int32;
using cs_vbyte = csbiginteger::cs_vbyte;

CSBIGINTEGER_EXTERN_C bool
csbiginteger_engine(char* sr, int sz_sr)
{
   std::string str = csbiginteger::BigInteger::getEngine();
   // check memory
   if (sz_sr < (int)str.length())
      return false;
   // copy to string
   std::copy(str.begin(), str.end(), sr);
   return true;
}

CSBIGINTEGER_EXTERN_C cs_int32
csbiginteger_init_empty(cs_byte* vr, int sz_vr)
{
   csbiginteger::BigInteger big;
   // copy to memory
   bool r = big.CopyTo(vr, sz_vr);
   // check for errors
   return r ? big.Length() : 0;
}

// initialize big integer and return its size (in bytes). output vr must be pre-allocated
CSBIGINTEGER_EXTERN_C cs_int32
csbiginteger_init_i(cs_int32 value, cs_byte* vr, int sz_vr)
{
   csbiginteger::BigInteger big(value);
   // copy to memory
   bool r = big.CopyTo(vr, sz_vr);
   // check for errors
   return r ? big.Length() : 0;
}

// initialize big integer and return its size (in bytes). output vr must be pre-allocated
CSBIGINTEGER_EXTERN_C cs_int32
csbiginteger_init_l(cs_int64 value, cs_byte* vr, int sz_vr)
{
   csbiginteger::BigInteger big(value);
   // copy to memory
   bool r = big.CopyTo(vr, sz_vr);
   // check for errors
   return r ? big.Length() : 0;
}

// initialize big integer and return its size (in bytes). output vr must be pre-allocated
CSBIGINTEGER_EXTERN_C cs_int32
csbiginteger_init_s(char* value, int base, cs_byte* vr, int sz_vr)
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
CSBIGINTEGER_EXTERN_C bool
csbiginteger_to_string(cs_byte* vb, int sz_vb, int base, char* sr, int sz_sr)
{
   csbiginteger::BigInteger big(cs_vbyte(vb, vb + sz_vb));
   std::string str = big.ToString(base);
   // check memory
   if (sz_sr < (int)str.length())
      return false;
   // copy to string
   std::copy(str.begin(), str.end(), sr);
   return true;
}

CSBIGINTEGER_EXTERN_C cs_int32
csbiginteger_to_int(cs_byte* vb, int sz_vb)
{
   csbiginteger::BigInteger big(cs_vbyte(vb, vb + sz_vb));
   int x = big.toInt();
   return x;
}

CSBIGINTEGER_EXTERN_C cs_int64
csbiginteger_to_long(cs_byte* vb, int sz_vb)
{
   csbiginteger::BigInteger big(cs_vbyte(vb, vb + sz_vb));
   long x = big.toLong();
   return x;
}

// =======================
// csbiginteger operations
// =======================

// perform big1 == big2
CSBIGINTEGER_EXTERN_C bool
csbiginteger_eq(cs_byte* big1, int sz_big1, cs_byte* big2, int sz_big2)
{
   csbiginteger::BigInteger b1(cs_vbyte(big1, big1 + sz_big1));
   csbiginteger::BigInteger b2(cs_vbyte(big2, big2 + sz_big2));
   return b1 == b2;
}

// perform big1 < big2
CSBIGINTEGER_EXTERN_C bool
csbiginteger_lt(cs_byte* big1, int sz_big1, cs_byte* big2, int sz_big2)
{
   csbiginteger::BigInteger b1(cs_vbyte(big1, big1 + sz_big1));
   csbiginteger::BigInteger b2(cs_vbyte(big2, big2 + sz_big2));
   return b1 < b2;
}

// perform big1 > big2
CSBIGINTEGER_EXTERN_C bool
csbiginteger_gt(cs_byte* big1, int sz_big1, cs_byte* big2, int sz_big2)
{
   csbiginteger::BigInteger b1(cs_vbyte(big1, big1 + sz_big1));
   csbiginteger::BigInteger b2(cs_vbyte(big2, big2 + sz_big2));
   return b1 > b2;
}

// perform big1 + big2 and return its size (in bytes). output vr must be pre-allocated
CSBIGINTEGER_EXTERN_C cs_int32
csbiginteger_add(cs_byte* big1, int sz_big1, cs_byte* big2, int sz_big2, cs_byte* vr, int sz_vr)
{
   csbiginteger::BigInteger b1(cs_vbyte(big1, big1 + sz_big1));
   csbiginteger::BigInteger b2(cs_vbyte(big2, big2 + sz_big2));
   csbiginteger::BigInteger b3 = b1 + b2;
   if (b3 == csbiginteger::BigInteger::Error())
      return 0; // error
   if (!b3.CopyTo(vr, sz_vr))
      return 0; // error
   return b3.Length();
}

// perform big1 - big2 and return its size (in bytes). output vr must be pre-allocated
CSBIGINTEGER_EXTERN_C cs_int32
csbiginteger_sub(cs_byte* big1, int sz_big1, cs_byte* big2, int sz_big2, cs_byte* vr, int sz_vr)
{
   csbiginteger::BigInteger b1(cs_vbyte(big1, big1 + sz_big1));
   csbiginteger::BigInteger b2(cs_vbyte(big2, big2 + sz_big2));
   csbiginteger::BigInteger b3 = b1 - b2;
   if (b3 == csbiginteger::BigInteger::Error())
      return 0; // error
   if (!b3.CopyTo(vr, sz_vr))
      return 0; // error
   return b3.Length();
}

// perform big1 * big2 and return its size (in bytes). output vr must be pre-allocated
CSBIGINTEGER_EXTERN_C cs_int32
csbiginteger_mul(cs_byte* big1, int sz_big1, cs_byte* big2, int sz_big2, cs_byte* vr, int sz_vr)
{
   csbiginteger::BigInteger b1(cs_vbyte(big1, big1 + sz_big1));
   csbiginteger::BigInteger b2(cs_vbyte(big2, big2 + sz_big2));
   csbiginteger::BigInteger b3 = b1 * b2;
   if (b3 == csbiginteger::BigInteger::Error())
      return 0; // error
   if (!b3.CopyTo(vr, sz_vr))
      return 0; // error
   return b3.Length();
}

// perform big1 / big2 and return its size (in bytes). output vr must be pre-allocated
CSBIGINTEGER_EXTERN_C cs_int32
csbiginteger_div(cs_byte* big1, int sz_big1, cs_byte* big2, int sz_big2, cs_byte* vr, int sz_vr)
{
   csbiginteger::BigInteger b1(cs_vbyte(big1, big1 + sz_big1));
   csbiginteger::BigInteger b2(cs_vbyte(big2, big2 + sz_big2));
   csbiginteger::BigInteger b3 = b1 / b2;
   if (b3 == csbiginteger::BigInteger::Error())
      return 0; // error
   if (!b3.CopyTo(vr, sz_vr))
      return 0; // error
   return b3.Length();
}

// perform big1 % big2 and return its size (in bytes). output vr must be pre-allocated
CSBIGINTEGER_EXTERN_C cs_int32
csbiginteger_mod(cs_byte* big1, int sz_big1, cs_byte* big2, int sz_big2, cs_byte* vr, int sz_vr)
{
   csbiginteger::BigInteger b1(cs_vbyte(big1, big1 + sz_big1));
   csbiginteger::BigInteger b2(cs_vbyte(big2, big2 + sz_big2));
   csbiginteger::BigInteger b3 = b1 % b2;
   if (b3 == csbiginteger::BigInteger::Error())
      return 0; // error
   if (!b3.CopyTo(vr, sz_vr))
      return 0; // error
   return b3.Length();
}

// perform big1 << big2 and return its size (in bytes). output vr must be pre-allocated
CSBIGINTEGER_EXTERN_C cs_int32
csbiginteger_shl(cs_byte* big1, int sz_big1, cs_byte* big2, int sz_big2, cs_byte* vr, int sz_vr)
{
   csbiginteger::BigInteger b1(cs_vbyte(big1, big1 + sz_big1));
   csbiginteger::BigInteger b2(cs_vbyte(big2, big2 + sz_big2));
   csbiginteger::BigInteger b3 = b1 << b2;
   if (b3 == csbiginteger::BigInteger::Error())
      return 0; // error
   if (!b3.CopyTo(vr, sz_vr))
      return 0; // error
   return b3.Length();
}

// perform big1 >> big2 and return its size (in bytes). output vr must be pre-allocated
CSBIGINTEGER_EXTERN_C cs_int32
csbiginteger_shr(cs_byte* big1, int sz_big1, cs_byte* big2, int sz_big2, cs_byte* vr, int sz_vr)
{
   csbiginteger::BigInteger b1(cs_vbyte(big1, big1 + sz_big1));
   csbiginteger::BigInteger b2(cs_vbyte(big2, big2 + sz_big2));
   csbiginteger::BigInteger b3 = b1 >> b2;
   if (b3 == csbiginteger::BigInteger::Error())
      return 0; // error
   if (!b3.CopyTo(vr, sz_vr))
      return 0; // error
   return b3.Length();
}

// perform big ^ int32 and return its size (in bytes). output vr must be pre-allocated
CSBIGINTEGER_EXTERN_C cs_int32
csbiginteger_pow(cs_byte* big, int sz_big, int exp, cs_byte* vr, int sz_vr)
{
   csbiginteger::BigInteger b1(cs_vbyte(big, big + sz_big));
   csbiginteger::BigInteger b3 = csbiginteger::BigInteger::Pow(b1, exp);
   if (b3 == csbiginteger::BigInteger::Error())
      return 0; // error
   if (!b3.CopyTo(vr, sz_vr))
      return 0; // error
   return b3.Length();
}