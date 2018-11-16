#ifndef __ENGINE_H__
#define __ENGINE_H__

#include <stdint.h>
#include <string>

#ifdef WINDOWS
    #ifdef ENGINE_EXPORT
        #define ENGINE_API __declspec(dllexport)
    #else
        #define ENGINE_API __declspec(dllimport)
    #endif
#elif LINUX
    #define ENGINE_API __attribute__ ((visibility ("default")))
#else
    #error "OS not supported"
#endif

namespace Engine {

typedef struct {
    uint16_t    window_width;
    uint16_t    window_height;
    std::string window_title;
} engine_config_t;

ENGINE_API void init( engine_config_t* engine_config );
ENGINE_API void run();
ENGINE_API void shutdown();

} // end namespace Engine


#endif //__ENGINE_H__
