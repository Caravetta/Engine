#ifndef __CORE_COMMON_H__
#define __CORE_COMMON_H__

#include <iostream>
#include <stdint.h>
#include<typeinfo>
//#include<cxxabi.h>
#include "core_return.h"
#include <vector>
#include <ctime>
#include <ratio>
#include <chrono>

#define USE_BASE_MALLOC 0

#ifdef WINDOWS_PLATFORM
    #ifdef CORE_EXPORT
        #define CORE_API __declspec(dllexport)
    #else
        #define CORE_API __declspec(dllimport)
    #endif
#else
    #define CORE_API
#endif

#ifdef WINDOWS_PLATFORM
    #define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#else
    #define __FILENAME__ __FILE__
#endif

#define LOG(...) PRINT("INFO", __VA_ARGS__);
#define LOG_WARN(...) PRINT("WARN", __VA_ARGS__);
#define LOG_ERROR(...) PRINT("ERROR", __VA_ARGS__);

#ifdef DEBUG_BUILD
    #define DEBUG_LOG(...) PRINT("DEBUG", __VA_ARGS__);
    #define CHECK( expr ) CHECK_INFO( expr, "" )
    #define CHECK_INFO( expr, ... ){                                                                                           \
    if ( !(expr) ) {                                                                                                                                                        \
        std::cout << __DATE__ << " - " << __TIME__ << " - " << "ERROR" << " - " << __FILENAME__ << " - " << __LINE__ << ": ";                                               \
        std::cout << "Assertion error [" << #expr << "] in " << __FUNCTION__ << "() at line " << __LINE__ << " in file " << __FILENAME__ << " " << __VA_ARGS__ << std::endl;\
    }                                                                                                                                                                       \
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

#ifdef WINDOWS_PLATFORM
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

typedef std::vector<uint8_t> Array;

template<typename T>
struct BaseType { typedef T type; };
template<typename T>
struct BaseType<T*> { typedef typename BaseType<T>::type type; };

#ifdef WINDOWS_PLATFORM
template<typename T>
const char* realname (T &obj)
{
  return abi::__cxa_demangle(typeid(obj).name(), 0, 0, 0);
}
#endif

#endif //__CORE_COMMON_H__
