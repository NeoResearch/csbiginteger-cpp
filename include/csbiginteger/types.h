// SPDX-License-Identifier:  MIT
// Copyright (C) 2020-2022 - csbiginteger-cpp project

#ifndef CSBIGINTEGER_TYPES_H
#define CSBIGINTEGER_TYPES_H

// only c types here (not vector)

#include <cstdint>

namespace csbiginteger {

using cs_byte = unsigned char;
static_assert(sizeof(cs_byte) == 1);

using cs_int32 = int;
static_assert(sizeof(cs_int32) == 4);

using cs_uint32 = unsigned int;
static_assert(sizeof(cs_uint32) == 4);

using cs_int64 = int64_t;
static_assert(sizeof(cs_int64) == 8);

using cs_uint64 = uint64_t;
static_assert(sizeof(cs_uint64) == 8);

}  // namespace csbiginteger

#endif  // CSBIGINTEGER_TYPES_H