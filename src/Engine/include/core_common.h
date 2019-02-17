#ifndef __CORE_H__
#define __CORE_H__

#include <iostream>
#include <stdint.h>
#include<typeinfo>
//#include<cxxabi.h>
#include <vector>
#include <string>
#include <cstring>
#include <ctime>
#include <ratio>
#include <chrono>
#include "Engine.h"

#ifdef WINDOWS
    #define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#else
    #define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#endif

#define LOG(...) PRINT("INFO", __VA_ARGS__);
#define LOG_WARN(...) PRINT("WARN", __VA_ARGS__);
#define LOG_ERROR(...) PRINT("ERROR", __VA_ARGS__);

#ifdef DEBUG_BUILD
    #define DEBUG_LOG(...) PRINT("DEBUG", __VA_ARGS__);
    #define CHECK( expr ) CHECK_INFO( expr, "" )
    #define CHECK_INFO( expr, ... ){                                                                                           \
    if ( !(expr) ) {                                                                                                           \
        std::cout << __DATE__ << " - " << __TIME__ << " - " << "ERROR" << " - " << __FILENAME__ << " - " << __LINE__ << ": ";  \
        std::cout << "Assertion error [" << #expr << "] in " << __FUNCTION__ << "() at line " << __LINE__ << " in file ";      \
	std::cout << __FILENAME__ << " " << __VA_ARGS__ << std::endl;							       \
    }                                                                                                                          \
    }
#else
    #define DEBUG_LOG(...) while(false){}
    #define CHECK_INFO( expr, ... ) while(false){}
    #define CHECK( expr ) while(false){}
#endif

#define PRINT(level,...){                                                                                       \
    std::cout << __DATE__ << " - " << __TIME__ << " - " << level << " - " << __FILENAME__ << " - " << __LINE__; \
    std::cout << ": " << __VA_ARGS__ << std::endl;                                                              \
}

#define ALLOC_RETURN_FAILURE( var, ... ) {  \
    var = new (std::nothrow) __VA_ARGS__;   \
    CHECK( var != NULL );                   \
    if ( var == NULL ) {                    \
        return MEMORY_ALLOC_FAILED;         \
    }                                       \
}

#ifdef WINDOWS
    #define ALWAYS_INLINE __forceinline
#else
    #define ALWAYS_INLINE
#endif

#define U8_MAX  255
#define U16_MAX 65535
#define U32_MAX 4294967295
#define U64_MAX 18446744073709551615

#define PASTE_TOKEN( value, token ) value ## token
#define PASTE_LINE( value , line ) PASTE_TOKEN( value, line)

//#define TIME_ENABLE 1

#ifdef TIME_ENABLE
    #define START_TIME_BLOCK( name )                                                            \
        Function_Perf::get_instance()->set_current_node( #name );                               \
        std::chrono::steady_clock::time_point name ## t1 = std::chrono::steady_clock::now();
    #define END_TIME_BLOCK( name )                                                                                                              \
        std::chrono::steady_clock::time_point name ## t2 = std::chrono::steady_clock::now();                                                    \
        std::chrono::duration<double> name ## time_span = std::chrono::duration_cast<std::chrono::duration<double>>( name ## t2 - name ## t1 ); \
        Function_Perf::get_instance()->set_time_value((name ## time_span).count(), #name);
    #define PRINT_TIME_BLOCKS() Function_Perf::get_instance()->print();
#else
    #define START_TIME_BLOCK( name ) while(false){}
    #define END_TIME_BLOCK( name ) while(false){}
    #define PRINT_TIME_BLOCKS() while(false){}
#endif

#define HANDLE_SET_ACTIVE 1
#define HANDLE_SET_NON_ACTIVE 0

#ifdef WINDOWS
    #define START_SUPPRESS_WARNING( x, y ) __pragma(warning(suppress: x))
    #define END_SUPPRESS_WARNING( x, y )
#else
    #define START_SUPPRESS_WARNING( x, y )
    #define END_SUPPRESS_WARNING( x, y )
#endif

#define UNUSED_ARG( x ) ((void)(x))

#define UNORDERED_MAP_ITERATOR( x, y ) std::unordered_map<x, y>::const_iterator

typedef std::vector<uint8_t> Array;

template<typename T>
struct BaseType { typedef T type; };
template<typename T>
struct BaseType<T*> { typedef typename BaseType<T>::type type; };


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


#ifdef WINDOWS
template<typename T>
const char* realname (T &obj)
{
  return abi::__cxa_demangle(typeid(obj).name(), 0, 0, 0);
}
#endif

#endif //__CORE_H__
