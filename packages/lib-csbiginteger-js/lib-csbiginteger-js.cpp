// AUTOMATICALLY GENERATED FILE - DO NOT EDIT THIS
//
// building lib-neopt-core in javascript (via emscripten)
//
#include <emscripten.h>
//
// for helper prints and strings
//#include <iostream>
//#include <string>
//#include <assert.h>

// =======================================================================================
// these are C++ methods provided to emscripten (js part) via connection on C++ Neo3 Core
//
#include <BigInteger.h>
#include <HandBigInt.hpp>
#include <BigIntegerHand.cpp> // TODO: never try that at home!

#define CSBIGINTEGER_EXTERN_C extern "C" EMSCRIPTEN_KEEPALIVE

#include <csBigIntegerLib.h>
#include <csBigIntegerLib.cpp> // TODO: never try that at home!

// ============= begin library


CSBIGINTEGER_EXTERN_C
int 
csbiginteger_external_welcome(const char* bn1, const char* bn_out, unsigned char* u_out);
// implementation is on 'csbiginteger_web_exports.js'


CSBIGINTEGER_EXTERN_C
int
csbiginteger_welcome(int x) {
   //std::cout << "greetings from csbiginteger" << std::endl;
   std::string str("hello");
   std::string str_out("world");
   unsigned char ustr[10];
   //
   const char* bn1 = str.c_str();
   const char* bn_out = str_out.c_str();
   unsigned char* u_out = ustr;
   int y = csbiginteger_external_welcome(bn1, bn_out, u_out);
   return x+y+u_out[0];
}
