#include "csBigIntegerLib.h"

// import big integer
#include "BigInteger.h"

using namespace csbiginteger;

extern "C" int32
csbiginteger_init_empty(byte* vr, int sz_vr)
{
   BigInteger big;
   // copy to memory
   bool r = big.CopyTo(vr, sz_vr);
   // check for errors
   return r ? big.Length() : 0;
}

// initialize big integer and return its size (in bytes). output vr must be pre-allocated
extern "C" int32
csbiginteger_init_i(int32 value, byte* vr, int sz_vr)
{
   BigInteger big(value);
   // copy to memory
   bool r = big.CopyTo(vr, sz_vr);
   // check for errors
   return r ? big.Length() : 0;
}

// initialize big integer and return its size (in bytes). output vr must be pre-allocated
extern "C" int32
csbiginteger_init_l(int64 value, byte* vr, int sz_vr)
{
   BigInteger big(value);
   // copy to memory
   bool r = big.CopyTo(vr, sz_vr);
   // check for errors
   return r ? big.Length() : 0;
}

// initialize big integer and return its size (in bytes). output vr must be pre-allocated
extern "C" int32
csbiginteger_init_s(char* value, int base, byte* vr, int sz_vr)
{
   BigInteger big(std::string(value), base);
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
   BigInteger big(vbyte(vb, vb + sz_vb));
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
   BigInteger big(vbyte(vb, vb + sz_vb));
   int x = big.toInt();
   return x;
}

extern "C" long
csbiginteger_to_long(byte* vb, int sz_vb)
{
   BigInteger big(vbyte(vb, vb + sz_vb));
   long x = big.toLong();
   return x;
}


/*

// =======================
// csbiginteger operations
// =======================

// perform big1 + big2 and return its size (in bytes). output vr must be pre-allocated
extern "C" int32
csbiginteger_add(byte* big1, int sz_big1, byte* big2, int sz_big2, byte* vr, int sz_vr);

// perform big1 - big2 and return its size (in bytes). output vr must be pre-allocated
extern "C" int32
csbiginteger_sub(byte* big1, int sz_big1, byte* big2, int sz_big2, byte* vr, int sz_vr);

*/
