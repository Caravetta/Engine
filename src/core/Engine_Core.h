#ifndef __ENGINE_CORE_H__
#define __ENGINE_CORE_H__

#include "ecs.h"

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

namespace Engine {

/****************************************/
/*                                      */
/*         Basic Engine Calls           */
/*                                      */
/****************************************/

ENGINE_API Rc_t init( void );
ENGINE_API void shutdown( void );

} // end namespace Engine

#endif //__ENGINE_CORE_H__
