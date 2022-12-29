#ifndef CSBIGINTEGER_LIB_H
#define CSBIGINTEGER_LIB_H

#include <stdio.h>

#include "types.h"

using cs_int32 = csbiginteger::cs_int32;
using cs_int64 = csbiginteger::cs_int64;
using cs_byte = csbiginteger::cs_byte;

#ifndef CSBIGINTEGER_EXTERN_C
#define CSBIGINTEGER_EXTERN_C extern "C"
#endif

// get engine. output sr must be pre-allocated (return indicates failure, 'true' is fine)
CSBIGINTEGER_EXTERN_C bool
csbiginteger_engine(char* sr, int sz_sr);

// =====================

// initialize big integer and return its size (in bytes). output vr must be pre-allocated
CSBIGINTEGER_EXTERN_C cs_int32
csbiginteger_init_empty(cs_byte* vr, int sz_vr);

// initialize big integer and return its size (in bytes). output vr must be pre-allocated
CSBIGINTEGER_EXTERN_C cs_int32
csbiginteger_init_i(cs_int32 value, cs_byte* vr, int sz_vr);

// initialize big integer and return its size (in bytes). output vr must be pre-allocated
CSBIGINTEGER_EXTERN_C cs_int32
csbiginteger_init_l(cs_int64 value, cs_byte* vr, int sz_vr);

// initialize big integer and return its size (in bytes). output vr must be pre-allocated
CSBIGINTEGER_EXTERN_C cs_int32
csbiginteger_init_s(char* value, cs_int32 base, cs_byte* vr, int sz_vr);

// ================
// auxiliar methods
// ================

// ToString(base). input vb and output sr must be pre-allocated (return indicates failure, 'true' is fine)
CSBIGINTEGER_EXTERN_C bool
csbiginteger_to_string(cs_byte* vb, int sz_vb, int base, char* sr, int sz_sr);

// toInt(). input vb must be pre-allocated
CSBIGINTEGER_EXTERN_C cs_int32
csbiginteger_to_int(cs_byte* vb, int sz_vb);

// toLong(). input vb must be pre-allocated
CSBIGINTEGER_EXTERN_C cs_int64
csbiginteger_to_long(cs_byte* vb, int sz_vb);

// =======================
// csbiginteger operations
// =======================

// perform big1 == big2
CSBIGINTEGER_EXTERN_C bool
csbiginteger_eq(cs_byte* big1, int sz_big1, cs_byte* big2, int sz_big2);

// perform big1 > big2
CSBIGINTEGER_EXTERN_C bool
csbiginteger_gt(cs_byte* big1, int sz_big1, cs_byte* big2, int sz_big2);

// perform big1 < big2
CSBIGINTEGER_EXTERN_C bool
csbiginteger_lt(cs_byte* big1, int sz_big1, cs_byte* big2, int sz_big2);

// ------------------- arithmetic ---------------------

// perform big1 + big2 and return its size (in bytes). output vr must be pre-allocated
CSBIGINTEGER_EXTERN_C cs_int32
csbiginteger_add(cs_byte* big1, int sz_big1, cs_byte* big2, int sz_big2, cs_byte* vr, int sz_vr);

// perform big1 - big2 and return its size (in bytes). output vr must be pre-allocated
CSBIGINTEGER_EXTERN_C cs_int32
csbiginteger_sub(cs_byte* big1, int sz_big1, cs_byte* big2, int sz_big2, cs_byte* vr, int sz_vr);

// perform big1 * big2 and return its size (in bytes). output vr must be pre-allocated
CSBIGINTEGER_EXTERN_C cs_int32
csbiginteger_mul(cs_byte* big1, int sz_big1, cs_byte* big2, int sz_big2, cs_byte* vr, int sz_vr);

// perform big1 / big2 and return its size (in bytes). output vr must be pre-allocated
CSBIGINTEGER_EXTERN_C cs_int32
csbiginteger_div(cs_byte* big1, int sz_big1, cs_byte* big2, int sz_big2, cs_byte* vr, int sz_vr);

// perform big1 % big2 and return its size (in bytes). output vr must be pre-allocated
CSBIGINTEGER_EXTERN_C cs_int32
csbiginteger_mod(cs_byte* big1, int sz_big1, cs_byte* big2, int sz_big2, cs_byte* vr, int sz_vr);

// perform big1 >> big2 and return its size (in bytes). output vr must be pre-allocated
CSBIGINTEGER_EXTERN_C cs_int32
csbiginteger_shr(cs_byte* big1, int sz_big1, cs_byte* big2, int sz_big2, cs_byte* vr, int sz_vr);

// perform big1 << big2 and return its size (in bytes). output vr must be pre-allocated
CSBIGINTEGER_EXTERN_C cs_int32
csbiginteger_shl(cs_byte* big1, int sz_big1, cs_byte* big2, int sz_big2, cs_byte* vr, int sz_vr);

// perform big ^ int32 and return its size (in bytes). output vr must be pre-allocated
CSBIGINTEGER_EXTERN_C cs_int32
csbiginteger_pow(cs_byte* big, int sz_big, int exp, cs_byte* vr, int sz_vr);

#endif // CSBIGINTEGER_LIB_H
