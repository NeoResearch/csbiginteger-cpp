#ifndef CSBIGINTEGER_TYPES_H
#define CSBIGINTEGER_TYPES_H

// only c types here (not vector)

namespace csbiginteger {

using cs_byte = unsigned char;
static_assert(sizeof(cs_byte) == 1);

using cs_int32 = int;
static_assert(sizeof(cs_int32) == 4);

using cs_uint32 = unsigned int;
static_assert(sizeof(cs_uint32) == 4);

using cs_int64 = long long;
static_assert(sizeof(cs_int64) == 8);

using cs_uint64 = unsigned long long;
static_assert(sizeof(cs_uint64) == 8);

} // namespace csbiginteger

#endif // CSBIGINTEGER_TYPES_H