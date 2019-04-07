#ifndef __CORE_COMMON_H__
#define __CORE_COMMON_H__

#include <stdint.h>
#include "return_codes.h"

typedef int8_t  int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;
typedef int32_t bool32;

typedef int8   s8;
typedef int16  s16;
typedef int32  s32;
typedef int64  s64;
typedef bool32 b32;

typedef uint8_t  uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

typedef uint8  u8;
typedef uint16 u16;
typedef uint32 u32;
typedef uint64 u64;

typedef float  float32;
typedef double float64;

typedef float32 f32;
typedef float64 f64;

#define UNUSED_ARG( x ) ((void)(x))

#define CHECK( condition )

#endif //__CORE_COMMON_H__
