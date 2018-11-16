#ifndef __CORE_H__
#define __CORE_H__

#ifdef PLATFORM_WINDOWS
    #ifdef ENGINE_EXPORT
        #define ENGINE_API __declspec(dllexport)
    #else
        #define ENGINE_API __declspec(dllimport)
    #endif
#else
    #error "SHOULD NOT BE HERE"
    #define ENGINE_API
#endif

#endif //__CORE_H__
