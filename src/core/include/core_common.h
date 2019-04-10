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
#elif LINUX
    #define ENGINE_API __attribute__ ((visibility ("default")))
#else
    #define ENGINE_API
#endif

#define UNUSED_ARG( x ) ((void)(x))

#define COMPONENT()
#define TAG()

#define CHECK( condition )

#define LOG( ... ) printf( __VA_ARGS__ ); printf("\n");
#define LOG_ERROR(...) printf( __VA_ARGS__ ); printf("\n");

} // end namespace Engine

#endif //__CORE_COMMON_H__
