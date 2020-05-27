
#include "BigInteger.h"

#include <cstdlib>
#include <iostream>
#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/debug-helpers.h>
#include <string>
#pragma comment(lib, "mono-2.0.lib")

using namespace std;
using namespace csbiginteger;

// =======================

MonoDomain* domain = mono_jit_init("MonoScriptTry");

// TODO: use AOT (ahead-of-time compilation) on csbiginteger_dotnet.dll.so
string asmPath = "csbiginteger_dotnet.dll"; 

MonoAssembly* assembly = mono_domain_assembly_open(domain, asmPath.c_str());

MonoImage* image = mono_assembly_get_image(assembly);

MonoClass* biglibclass = mono_class_from_name(image, "csbiglib", "BigIntegerLib");

string
mono_string_to_string(MonoString* str)
{
   mono_unichar2* chl = mono_string_chars(str);
   string out("");
   for (int i = 0; i < mono_string_length(str); i++) {
      out += chl[i];
   }
   return out;
};

cs_vbyte
mono_bytearray_to_bytearray(MonoArray* arr)
{
   unsigned int size = mono_array_length(arr);
   vbyte bytes(size, 0x00);
   for (unsigned i = 0; i < size; i++)
      bytes[i] = mono_array_get(arr, unsigned char, i);
   return bytes;
};

MonoArray*
CreateByteArray(cs_vbyte bytes)
{
   MonoArray* data;

   data = mono_array_new(domain, mono_get_byte_class(), bytes.size());
   for (unsigned i = 0; i < bytes.size(); i++)
      mono_array_set(data, unsigned char, i, bytes[i]);

   return data;
}

MonoObject*
executeOp(std::string op, cs_vbyte bytes1, cs_vbyte bytes2)
{
   MonoObject* bigLib = mono_object_new(domain, biglibclass);
   mono_runtime_object_init(bigLib);

   string sMyMethodStr = op;
   MonoMethodDesc* MyMethod = mono_method_desc_new(sMyMethodStr.c_str(), false);
   if (!MyMethod) {
      std::cout << "mono_method_desc_new failed" << std::endl;
      exit(1);
   }

   MonoMethod* method = mono_method_desc_search_in_image(MyMethod, image);
   if (!method) {
      std::cout << "mono_method_desc_search_in_image ::executeOp() failed" << std::endl;
      exit(1);
   }

   MonoArray* byteArray1 = ::CreateByteArray(bytes1);
   MonoArray* byteArray2 = ::CreateByteArray(bytes2);
   void* args[2];
   args[0] = byteArray1;
   args[1] = byteArray2;

   MonoObject* ret = mono_runtime_invoke(method, bigLib, args, nullptr);
   return ret;
}

// =======================

const BigInteger BigInteger::Zero = BigInteger(0);
const BigInteger BigInteger::One = BigInteger(1);
const BigInteger BigInteger::MinusOne = BigInteger(-1);
const BigInteger BigInteger::Error = error();

std::string
BigInteger::getEngine()
{
   return "Mono";   
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
   if (exponent < 0)
      return BigInteger::Error;
   MonoObject* bigLib = mono_object_new(domain, biglibclass);
   mono_runtime_object_init(bigLib);

   string sMyMethodStr = "BigIntegerLib:pow(byte[],int)";
   MonoMethodDesc* MyMethod = mono_method_desc_new(sMyMethodStr.c_str(), false);
   if (!MyMethod) {
      std::cout << "mono_method_desc_new failed" << std::endl;
      exit(1);
   }

   MonoMethod* method = mono_method_desc_search_in_image(MyMethod, image);
   if (!method) {
      std::cout << "mono_method_desc_search_in_image Pow() failed" << std::endl;
      exit(1);
   }

   MonoArray* byteArray1 = ::CreateByteArray(value.ToByteArray());
   void* args[2];
   args[0] = byteArray1;
   args[1] = &exponent;

   MonoObject* retarr = mono_runtime_invoke(method, bigLib, args, nullptr);

   MonoArray* arr = (MonoArray*)retarr;
   return BigInteger(mono_bytearray_to_bytearray(arr));
}

// default is base 10
// allows base 2
// if base 16, prefix '0x' indicates big-endian, otherwise is little-endian
BigInteger::BigInteger(string str, int base)
{
   MonoObject* bigLib = mono_object_new(domain, biglibclass);
   mono_runtime_object_init(bigLib);

   string sMyMethodStr = "BigIntegerLib:from_string_to_bytes(string,int)";
   MonoMethodDesc* MyMethod = mono_method_desc_new(sMyMethodStr.c_str(), false);
   if (!MyMethod) {
      std::cout << "mono_method_desc_new failed" << std::endl;
      exit(1);
   }

   MonoMethod* method = mono_method_desc_search_in_image(MyMethod, image);
   if (!method) {
      std::cout << "mono_method_desc_search_in_image BigInteger(str,int) failed" << std::endl;
      exit(1);
   }

   MonoString* monostr = mono_string_new(domain, str.c_str());
   void* args[2];
   args[0] = monostr;
   args[1] = &base;

   MonoObject* retarr = mono_runtime_invoke(method, bigLib, args, nullptr);

   MonoArray* arr = (MonoArray*)retarr;
   _data = mono_bytearray_to_bytearray(arr);
   std::reverse(_data.begin(), _data.end()); // to big-endian (internal)
}

BigInteger::BigInteger(float x)
{

   MonoObject* bigLib = mono_object_new(domain, biglibclass);
   mono_runtime_object_init(bigLib);

   string sMyMethodStr = "BigIntegerLib:from_float(single)";
   MonoMethodDesc* MyMethod = mono_method_desc_new(sMyMethodStr.c_str(), false);
   if (!MyMethod) {
      std::cout << "mono_method_desc_new failed" << std::endl;
      exit(1);
   }

   MonoMethod* method = mono_method_desc_search_in_image(MyMethod, image);
   if (!method) {
      std::cout << "mono_method_desc_search_in_image (float) failed" << std::endl;
      exit(1);
   }

   void* args[1];
   args[0] = &x;

   MonoObject* retarr = mono_runtime_invoke(method, bigLib, args, nullptr);

   MonoArray* arr = (MonoArray*)retarr;
   _data = mono_bytearray_to_bytearray(arr);
   std::reverse(_data.begin(), _data.end()); // to big-endian (internal)
}

string
BigInteger::toStringBase10() const
{
   MonoObject* bigLib = mono_object_new(domain, biglibclass);
   mono_runtime_object_init(bigLib);

   string sMyMethodStr = "BigIntegerLib:to_string(byte[],int)";
   MonoMethodDesc* MyMethod = mono_method_desc_new(sMyMethodStr.c_str(), false);
   if (!MyMethod) {
      std::cout << "mono_method_desc_new failed" << std::endl;
      exit(1);
   }

   MonoMethod* method = mono_method_desc_search_in_image(MyMethod, image);
   if (!method) {
      std::cout << "mono_method_desc_search_in_image toStringBase10 failed" << std::endl;
      exit(1);
   }

   MonoArray* byteArray = ::CreateByteArray(this->ToByteArray());
   //MonoString* monostr = mono_string_new(domain, str.c_str());
   void* args[2];
   int base = 10;
   args[0] = byteArray;
   args[1] = &base;

   MonoObject* retstr = mono_runtime_invoke(method, bigLib, args, nullptr);

   MonoString* strcast = (MonoString*)retstr;
   std::string sstr = mono_string_to_string(strcast);

   return sstr;
}

cs_int32
BigInteger::toInt() const
{
   MonoObject* bigLib = mono_object_new(domain, biglibclass);
   mono_runtime_object_init(bigLib);

   string sMyMethodStr = "BigIntegerLib:to_int32(byte[])";
   MonoMethodDesc* MyMethod = mono_method_desc_new(sMyMethodStr.c_str(), false);
   if (!MyMethod) {
      std::cout << "mono_method_desc_new failed" << std::endl;
      exit(1);
   }

   MonoMethod* method = mono_method_desc_search_in_image(MyMethod, image);
   if (!method) {
      std::cout << "mono_method_desc_search_in_image toInt() failed" << std::endl;
      exit(1);
   }

   MonoArray* byteArray = ::CreateByteArray(this->ToByteArray());
   void* args[1];
   args[0] = byteArray;

   MonoObject* ret = mono_runtime_invoke(method, bigLib, args, nullptr);

   int int_result = *(int*)mono_object_unbox(ret);
   return int_result;
}

cs_int64
BigInteger::toLong() const
{
   MonoObject* bigLib = mono_object_new(domain, biglibclass);
   mono_runtime_object_init(bigLib);

   string sMyMethodStr = "BigIntegerLib:to_int64(byte[])";
   MonoMethodDesc* MyMethod = mono_method_desc_new(sMyMethodStr.c_str(), false);
   if (!MyMethod) {
      std::cout << "mono_method_desc_new failed" << std::endl;
      exit(1);
   }

   MonoMethod* method = mono_method_desc_search_in_image(MyMethod, image);
   if (!method) {
      std::cout << "mono_method_desc_search_in_image toLong() failed" << std::endl;
      exit(1);
   }

   MonoArray* byteArray = ::CreateByteArray(this->ToByteArray());
   void* args[1];
   args[0] = byteArray;

   MonoObject* ret = mono_runtime_invoke(method, bigLib, args, nullptr);

   long long_result = *(long*)mono_object_unbox(ret);
   return long_result;
}

bool
BigInteger::operator>(const BigInteger& big2) const
{
   if (this->IsError() || big2.IsError())
      return false;

   string op = "BigIntegerLib:gt(byte[],byte[])";
   MonoObject* ret = ::executeOp(op, this->ToByteArray(), big2.ToByteArray());
   bool bool_result = *(bool*)mono_object_unbox(ret);
   return bool_result;
}

bool
BigInteger::operator<(const BigInteger& big2) const
{
   if (this->IsError() || big2.IsError()) {
      return false;
   }

   string op = "BigIntegerLib:lt(byte[],byte[])";
   MonoObject* ret = ::executeOp(op, this->ToByteArray(), big2.ToByteArray());
   bool bool_result = *(bool*)mono_object_unbox(ret);
   return bool_result;
}

// ----------------- arithmetic ---------------------

BigInteger
BigInteger::operator+(const BigInteger& big2) const
{
   if (this->IsError() || big2.IsError())
      return Error;

   string op = "BigIntegerLib:add(byte[],byte[])";
   MonoObject* retarr = ::executeOp(op, this->ToByteArray(), big2.ToByteArray());
   MonoArray* arr = (MonoArray*)retarr;
   return BigInteger(mono_bytearray_to_bytearray(arr));
}

BigInteger
BigInteger::operator-(const BigInteger& big2) const
{
   if (this->IsError() || big2.IsError())
      return Error;

   string op = "BigIntegerLib:sub(byte[],byte[])";
   MonoObject* retarr = ::executeOp(op, this->ToByteArray(), big2.ToByteArray());
   MonoArray* arr = (MonoArray*)retarr;
   return BigInteger(mono_bytearray_to_bytearray(arr));
}

BigInteger
  BigInteger::operator*(const BigInteger& big2) const
{
   if (this->IsError() || big2.IsError())
      return Error;

   string op = "BigIntegerLib:mul(byte[],byte[])";
   MonoObject* retarr = ::executeOp(op, this->ToByteArray(), big2.ToByteArray());
   MonoArray* arr = (MonoArray*)retarr;
   return BigInteger(mono_bytearray_to_bytearray(arr));
}

BigInteger
BigInteger::operator/(const BigInteger& big2) const
{
   if (this->IsError() || big2.IsError() || big2.IsZero())
      return Error;
   //cout << "dividing " << this->toInt() << " / " << big2.toInt() << " " << endl;
   //cout << "dividing " << this->ToString(16) << " / " << big2.ToString(16) << " " << endl;
   string op = "BigIntegerLib:div(byte[],byte[])";
   MonoObject* retarr = ::executeOp(op, this->ToByteArray(), big2.ToByteArray());
   MonoArray* arr = (MonoArray*)retarr;
   return BigInteger(mono_bytearray_to_bytearray(arr));
}

BigInteger
BigInteger::operator%(const BigInteger& big2) const
{
   if (this->IsError() || big2.IsError() || big2.IsZero())
      return Error;

   string op = "BigIntegerLib:mod(byte[],byte[])";
   MonoObject* retarr = ::executeOp(op, this->ToByteArray(), big2.ToByteArray());
   MonoArray* arr = (MonoArray*)retarr;
   return BigInteger(mono_bytearray_to_bytearray(arr));
}

BigInteger
BigInteger::operator<<(const BigInteger& big2) const
{
   if (this->IsError() || big2.IsError())
      return Error;
   if (big2 < Zero)
      return (*this) >> -big2;

   string op = "BigIntegerLib:shl(byte[],byte[])";
   MonoObject* retarr = ::executeOp(op, this->ToByteArray(), big2.ToByteArray());
   MonoArray* arr = (MonoArray*)retarr;
   return BigInteger(mono_bytearray_to_bytearray(arr));
}

BigInteger
BigInteger::operator>>(const BigInteger& big2) const
{
   if (this->IsError() || big2.IsError())
      return Error;
   if (big2 < Zero)
      return (*this) << -big2;

   string op = "BigIntegerLib:shr(byte[],byte[])";
   MonoObject* retarr = ::executeOp(op, this->ToByteArray(), big2.ToByteArray());
   MonoArray* arr = (MonoArray*)retarr;
   return BigInteger(mono_bytearray_to_bytearray(arr));
}
