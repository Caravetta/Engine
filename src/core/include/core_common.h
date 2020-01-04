#ifndef __CORE_COMMON_H__
#define __CORE_COMMON_H__

#include <cstdio>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include "return_codes.h"
#include "logger.h"

namespace Engine {

#ifdef WINDOWS
     //#ifdef ENGINE_EXPORT
          #define ENGINE_API __declspec(dllexport)
     //#else
          //#define ENGINE_API __declspec(dllimport)
     //#endif

     #define ALIGN_PRE( ALIGNMENT ) __declspec( align( ALIGNMENT ) )
     #define ALIGN_POST( ALIGNMENT )

     #define FORCE_INLINE __forceinline
#elif LINUX
     #define ENGINE_API __attribute__ ((visibility ("default")))

     #define GAME_API __attribute__ ((visibility ("default")))

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

//#define LOG( ... ) printf( __VA_ARGS__ ); printf("\n");
//#define LOG_ERROR(...) printf( __VA_ARGS__ ); printf("\n");

#define LOG( ... ) { \
        sprintf(Engine::Logger::tmp_log_buf, __VA_ARGS__);\
	Engine::Logger::get_instance()->log(Engine::Logger::tmp_log_buf, 0);\
	}

#define LOG_ERROR(...) { \
        sprintf(Engine::Logger::tmp_log_buf, __VA_ARGS__);\
	Engine::Logger::get_instance()->log(Engine::Logger::tmp_log_buf, 0);\
	}

#define NEAR_ZERO 1e-15f

} // end namespace Engine

#define EXTEN_PASTE( a, b ) a # b

#ifdef LINUX
     #include <dlfcn.h>

     #define LIB_HANDLE void*
     #define LIB_EXTENSION .so

     #define LIB_NAME( lib, exten ) EXTEN_PASTE(lib, exten)

     #define LOAD_LIB( lib )                                               \
          handle = dlopen(LIB_NAME(lib, LIB_EXTENSION), RTLD_LAZY);        \
          if ( handle == NULL ) {                                          \
               LOG("Failed to load lib %s", LIB_NAME(lib, LIB_EXTENSION)); \
               return Engine::ENGINE_ERROR;                                        \
          }                                                                \
          const char *dlsym_error = NULL;

     #define LOAD_LIB_FUNC( var )                      \
          dlerror();                                   \
          var = (var ## _proc)dlsym(handle, #var);     \
          dlsym_error = dlerror();                     \
          if ( dlsym_error ) {                         \
               LOG_ERROR("Failed to load " #var );     \
          }

     #define LOAD_LIB_FUNC_STRING( var, func_name )         \
          dlerror();                                        \
          var = (var ## _proc)dlsym(handle, func_name);     \
          dlsym_error = dlerror();                          \
          if ( dlsym_error ) {                              \
               LOG_ERROR("Failed to load " func_name );     \
          }

#elif WINDOWS
     #include <windows.h>

     #define LIB_HANDLE HINSTANCE
     #define LIB_EXTENSION .dll

     #define LIB_NAME( lib, exten ) EXTEN_PASTE(lib, exten)

     #define LOAD_LIB( lib )                                               \
          handle = LoadLibrary(LIB_NAME(lib, LIB_EXTENSION));              \
          if ( handle == NULL ) {                                          \
               LOG("Failed to load lib %s", LIB_NAME(lib, LIB_EXTENSION)); \
               return Engine::ENGINE_ERROR;                                        \
          }

     #define LOAD_LIB_FUNC( var )                           \
          var = (var ## _proc)GetProcAddress(handle, #var); \
          if ( var == NULL ) {                              \
               LOG_ERROR("Failed to load " #var );          \
          }

#else
     #error
#endif

typedef float float32_t;
typedef void (*mouse_position_cb)( int x_pos, int y_pos );
typedef void (*mouse_button_cb)( int button, bool is_pressed );
typedef void (*resize_cb)( int32_t width, int32_t height );

#endif //__CORE_COMMON_H__
