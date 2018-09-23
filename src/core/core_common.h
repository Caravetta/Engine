#if !defined(CORE_COMMON_H)

#include <iostream>
#include <stdint.h>
#include<typeinfo>
//#include<cxxabi.h>
#include "core_return.h"
#include <vector>

#define USE_BASE_MALLOC 0

#ifdef CORE_EXPORT
#define CORE_API __declspec(dllexport)
#else
#define CORE_API __declspec(dllimport)
#endif

#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)

#define LOG(...) PRINT("INFO", __VA_ARGS__);
#define LOG_WARN(...) PRINT("WARN", __VA_ARGS__);
#define LOG_ERROR(...) PRINT("ERROR", __VA_ARGS__);

#ifdef DEBUG_BUILD
#define DEBUG_LOG(...) PRINT("DEBUG", __VA_ARGS__);

#define CHECK( expr ) CHECK_INFO( expr, "" )

#define CHECK_INFO( expr, ... ){ \
    if ( !(expr) ) { \
        std::cout << __DATE__ << " - " << __TIME__ << " - " << "ERROR" << " - " << __FILENAME__ << " - " << __LINE__ << ": "; \
        std::cout << "Assertion error [" << #expr << "] in " << __FUNCTION__ << "() at line " << __LINE__ << " in file " << __FILENAME__ << " " << __VA_ARGS__ << std::endl; \
    } \
}
#else
#define DEBUG_LOG(...) while(false){}
#define CHECK_INFO( expr, ... ) while(false){}
#define CHECK( expr ) while(false){}
#endif

#define PRINT(level,...){ \
    std::cout << __DATE__ << " - " << __TIME__ << " - " << level << " - " << __FILENAME__ << " - " << __LINE__; \
    std::cout << ": " << __VA_ARGS__ << std::endl; \
}

#define ALLOC_RETURN_FAILURE( var, ... ) {  \
    var = new (std::nothrow) __VA_ARGS__;   \
    CHECK( var != NULL );                   \
    if ( var == NULL ) {                    \
        return MEMORY_ALLOC_FAILED;         \
    }                                       \
}

#define U8_MAX  255
#define U16_MAX 65535
#define U32_MAX 4294967295
#define U64_MAX 18446744073709551615

typedef std::vector<uint8_t> Array;

template<typename T>
struct BaseType { typedef T type; };
template<typename T>
struct BaseType<T*> { typedef typename BaseType<T>::type type; };

template<typename T>
const char* realname (T &obj)
{
  return abi::__cxa_demangle(typeid(obj).name(), 0, 0, 0);
}

#define CORE_COMMON_H
#endif
