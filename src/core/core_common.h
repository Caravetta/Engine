#if !defined(CORE_COMMON_H)

#include <iostream>
#include <stdint.h>
#include "core_return.h"

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

#define PRINT(level,...){ \
    std::cout << __DATE__ << " - " << __TIME__ << " - " << __FILENAME__ << " - " << __LINE__; \
    std::cout << " - " << level << ": " << __VA_ARGS__ << std::endl; \
}

#define CORE_COMMON_H
#endif
