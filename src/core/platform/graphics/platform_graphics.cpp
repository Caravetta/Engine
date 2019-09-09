#include "platform_graphics.h"

namespace Engine {

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
               return ENGINE_ERROR;                                        \
          }                                                                \
          const char *dlsym_error = NULL;

     #define LOAD_LIB_FUNC( var )                      \
          dlerror();                                   \
          var = (var ## _proc)dlsym(handle, #var);     \
          dlsym_error = dlerror();                     \
          if ( dlsym_error ) {                         \
               LOG_ERROR("Failed to load " #var );     \
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
               return ENGINE_ERROR;                                        \
          }

     #define LOAD_LIB_FUNC( var )                           \
          var = (var ## _proc)GetProcAddress(handle, #var); \
          if ( var == NULL ) {                              \
               LOG_ERROR("Failed to load " #var );          \
          }

#else
     #error
#endif

init_graphics_platform_proc init_graphics_platform     = NULL;
create_render_context_proc  create_render_context      = NULL;
swap_buffer_proc            swap_buffer                = NULL;
set_clear_color_proc        set_clear_color            = NULL;
graphics_clear_proc         graphics_clear             = NULL;
set_view_port_proc          set_view_port              = NULL;
enable_graphics_option_proc enable_graphics_option     = NULL;
set_depth_func_proc         set_depth_func             = NULL;
create_program_file_proc    create_program_file        = NULL;
create_program_string_proc  create_program_string      = NULL;
use_program_proc            use_program                = NULL;
fetch_uniform_id_proc       fetch_uniform_id           = NULL;
upload_uniform_float1_proc  upload_uniform_float1      = NULL;
upload_uniform_float2_proc  upload_uniform_float2      = NULL;
upload_uniform_float3_proc  upload_uniform_float3      = NULL;
upload_uniform_float4_proc  upload_uniform_float4      = NULL;
upload_uniform_mat4_proc    upload_uniform_mat4        = NULL;
create_vertex_array_proc    create_vertex_array        = NULL;
bind_vertex_array_proc      bind_vertex_array          = NULL;
create_vertex_buffer_proc   create_vertex_buffer       = NULL;
bind_vertex_buffer_proc     bind_vertex_buffer         = NULL;
buffer_vertex_data_proc     buffer_vertex_data         = NULL;
define_vertex_attrib_proc   define_vertex_attrib       = NULL;
enable_vertex_attrib_proc   enable_vertex_attrib       = NULL;
draw_data_proc              draw_data                  = NULL;


Rc_t load_graphics_api( Graphics_API graphics_api )
{
     LIB_HANDLE handle;
#ifdef LINUX
     LOAD_LIB("./libOpenGL");
#elif WINDOWS
     LOAD_LIB("./OpenGL");
#endif

     LOAD_LIB_FUNC(init_graphics_platform);
     LOAD_LIB_FUNC(create_render_context);
     LOAD_LIB_FUNC(swap_buffer);
     LOAD_LIB_FUNC(set_clear_color);
     LOAD_LIB_FUNC(graphics_clear);
     LOAD_LIB_FUNC(enable_graphics_option);
     LOAD_LIB_FUNC(set_depth_func);
     LOAD_LIB_FUNC(set_view_port);
     LOAD_LIB_FUNC(create_program_file);
     LOAD_LIB_FUNC(create_program_string);
     LOAD_LIB_FUNC(use_program);
     LOAD_LIB_FUNC(fetch_uniform_id);
     LOAD_LIB_FUNC(upload_uniform_float1);
     LOAD_LIB_FUNC(upload_uniform_float2);
     LOAD_LIB_FUNC(upload_uniform_float3);
     LOAD_LIB_FUNC(upload_uniform_float4);
     LOAD_LIB_FUNC(upload_uniform_mat4);
     LOAD_LIB_FUNC(create_vertex_array);
     LOAD_LIB_FUNC(bind_vertex_array);
     LOAD_LIB_FUNC(create_vertex_buffer);
     LOAD_LIB_FUNC(bind_vertex_buffer);
     LOAD_LIB_FUNC(buffer_vertex_data);
     LOAD_LIB_FUNC(define_vertex_attrib);
     LOAD_LIB_FUNC(enable_vertex_attrib);
     LOAD_LIB_FUNC(draw_data);

     init_graphics_platform();

     return SUCCESS;
}

} // end namespace Engine

