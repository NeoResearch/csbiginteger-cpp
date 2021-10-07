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
csbiginteger_welcome(int x) {
   //std::cout << "greetings from csbiginteger" << std::endl;
   return x+1;
}

