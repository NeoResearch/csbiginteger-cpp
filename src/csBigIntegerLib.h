#ifndef CSBIGINTEGER_LIB_H
#define CSBIGINTEGER_LIB_H

#include <stdio.h>

#include "types.h"

// initialize big integer and return its size (in bytes). output vr must be pre-allocated
extern "C" int32
csbiginteger_init_empty(byte* vr, int sz_vr);

// initialize big integer and return its size (in bytes). output vr must be pre-allocated
extern "C" int32
csbiginteger_init_i(int32 value, byte* vr, int sz_vr);

// initialize big integer and return its size (in bytes). output vr must be pre-allocated
extern "C" int32
csbiginteger_init_l(int64 value, byte* vr, int sz_vr);

// initialize big integer and return its size (in bytes). output vr must be pre-allocated
extern "C" int32
csbiginteger_init_s(char* value, int base, byte* vr, int sz_vr);

// ================
// auxiliar methods
// ================

// ToString(base). input vb and output sr must be pre-allocated (return indicates failure, 'true' is fine)
extern "C" bool
csbiginteger_to_string(byte* vb, int sz_vb, int base, char* sr, int sz_sr);

// toInt(). input vb must be pre-allocated
extern "C" int
csbiginteger_to_int(byte* vb, int sz_vb);

// toLong(). input vb must be pre-allocated
extern "C" long
csbiginteger_to_long(byte* vb, int sz_vb);

// =======================
// csbiginteger operations
// =======================

// perform big1 + big2 and return its size (in bytes). output vr must be pre-allocated
extern "C" int32
csbiginteger_add(byte* big1, int sz_big1, byte* big2, int sz_big2, byte* vr, int sz_vr);

// perform big1 - big2 and return its size (in bytes). output vr must be pre-allocated
extern "C" int32
csbiginteger_sub(byte* big1, int sz_big1, byte* big2, int sz_big2, byte* vr, int sz_vr);

// perform big1 * big2 and return its size (in bytes). output vr must be pre-allocated
extern "C" int32
csbiginteger_mul(byte* big1, int sz_big1, byte* big2, int sz_big2, byte* vr, int sz_vr);

// perform big1 / big2 and return its size (in bytes). output vr must be pre-allocated
extern "C" int32
csbiginteger_div(byte* big1, int sz_big1, byte* big2, int sz_big2, byte* vr, int sz_vr);

// perform big1 % big2 and return its size (in bytes). output vr must be pre-allocated
extern "C" int32
csbiginteger_mod(byte* big1, int sz_big1, byte* big2, int sz_big2, byte* vr, int sz_vr);

#endif // CSBIGINTEGER_LIB_H
