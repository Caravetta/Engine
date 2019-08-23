#ifndef __CORE_COMMON_H__
#define __CORE_COMMON_H__

#include <cstdio>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include "return_codes.h"

namespace Engine {

#ifdef WINDOWS
     #ifdef ENGINE_EXPORT
          #define ENGINE_API __declspec(dllexport)
     #else
          #define ENGINE_API __declspec(dllimport)
     #endif

     #define ALIGN_PRE( ALIGNMENT ) __declspec( align( ALIGNMENT ) )
     #define ALIGN_POST( ALIGNMENT )

     #define FORCE_INLINE __forceinline
#elif LINUX
     #define ENGINE_API __attribute__ ((visibility ("default")))

     #define ALIGN_PRE( ALIGNMENT )
     #define ALIGN_POST( ALIGNMENT ) __attribute__( ( aligned( ALIGNMENT ) ) )

     #define FORCE_INLINE inline __attribute__( ( always_inline ) )
#else
     #error
#endif

#ifdef CPU_X86
     #define ENGINE_SIMD_SSE 1
#else
     #error
#endif

#define UNUSED_ARG( x ) ((void)(x))

#define CHECK( condition )
#define CHECK_INFO( condition, print )

#define UNORDERED_MAP_ITER( x, y ) std::unordered_map<x, y>::const_iterator

#define LOG( ... ) printf( __VA_ARGS__ ); printf("\n");
#define LOG_ERROR(...) printf( __VA_ARGS__ ); printf("\n");

#define NEAR_ZERO 1e-15f

//typedef float float32_t;

} // end namespace Engine

typedef float float32_t;

#endif //__CORE_COMMON_H__
