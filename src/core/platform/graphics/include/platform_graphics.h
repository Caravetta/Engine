#ifndef __PLATFORM_GRAPHICS_H__
#define __PLATFORM_GRAPHICS_H__

#include "core_common.h"
#include "platform_graphics_common.h"

namespace Engine {

typedef Rc_t (*init_graphics_platform_proc) ( void );
typedef Rc_t (*create_render_context_proc) ( struct platform_window_t* window );
typedef void (*swap_buffer_proc) ( struct platform_window_t* window );
typedef void (*set_clear_color_proc) ( float r, float g, float b, float a );
typedef void (*graphics_clear_proc) ( uint64_t clear_mask );
typedef void (*enable_graphics_option_proc) ( Graphics_Option option );
typedef void (*disable_graphics_option_proc) ( Graphics_Option option );
typedef void (*set_depth_func_proc) ( Depth_Func type );
typedef void (*set_view_port_proc) ( int x, int y, size_t width, size_t height );
typedef int32_t (*create_program_file_proc) ( uint8_t* files );
typedef int32_t (*create_program_string_proc) ( uint8_t* strings );
typedef void (*use_program_proc) ( int32_t program_id );
typedef int32_t (*fetch_uniform_id_proc) ( int32_t program_id, uint8_t* name );
typedef void (*upload_uniform_int1_proc) ( int32_t location, int value );
typedef void (*upload_uniform_float1_proc) ( int32_t location, float value );
typedef void (*upload_uniform_float2_proc) ( int32_t location, float value_1, float value_2 );
typedef void (*upload_uniform_float3_proc) ( int32_t location, float value_1, float value_2, float value_3 );
typedef void (*upload_uniform_float4_proc) ( int32_t location, float value_1, float value_2, float value_3, float value_4 );
typedef void (*upload_uniform_mat4_proc) ( int32_t location, uint8_t* matrix );
typedef uint32_t (*create_vertex_array_proc) ( void );
typedef void (*bind_vertex_array_proc) ( uint32_t array_id );
typedef uint32_t (*create_vertex_buffer_proc) ( void );
typedef void (*bind_vertex_buffer_proc) ( Buffer_Type type, uint32_t buffer_id );
typedef void (*buffer_vertex_data_proc) ( Buffer_Type type, uint8_t* data, size_t size );
typedef void (*define_vertex_attrib_proc) ( uint32_t index, size_t size, Data_Type type, size_t stride, uint8_t* data );
typedef void (*enable_vertex_attrib_proc) ( uint32_t index );
typedef Fbo_Handle (*create_fbo_proc) ( void );
typedef void (*set_fbo_color_texture_proc) ( int color_texture );
typedef void (*delete_fbo_proc) ( Fbo_Handle fbo );
typedef void (*bind_fbo_proc) ( Fbo_Handle fbo );
typedef void (*unbind_fbo_proc) ( void );
typedef void (*bind_texture_proc) ( int texture_id );
typedef void (*draw_data_proc) ( Draw_Mode mode, int first, size_t count );
typedef void (*draw_elements_data_proc) ( Draw_Mode mode, int first, size_t count );
typedef Texture_Handle (*create_texture_proc) ( int width, int height, uint8_t* data, Texture_Format format );

extern init_graphics_platform_proc init_graphics_platform;
extern create_render_context_proc  create_render_context;
extern swap_buffer_proc            swap_buffer;
extern set_clear_color_proc        set_clear_color;
extern graphics_clear_proc         graphics_clear;
extern enable_graphics_option_proc enable_graphics_option;
extern disable_graphics_option_proc disable_graphics_option;
extern set_depth_func_proc         set_depth_func;
extern set_view_port_proc          set_view_port;
extern create_program_file_proc    create_program_file;
extern create_program_string_proc  create_program_string;
extern use_program_proc            use_program;
extern fetch_uniform_id_proc       fetch_uniform_id;
extern upload_uniform_int1_proc    upload_uniform_int1;
extern upload_uniform_float1_proc  upload_uniform_float1;
extern upload_uniform_float2_proc  upload_uniform_float2;
extern upload_uniform_float3_proc  upload_uniform_float3;
extern upload_uniform_float4_proc  upload_uniform_float4;
extern upload_uniform_mat4_proc    upload_uniform_mat4;
extern create_vertex_array_proc    create_vertex_array;
extern bind_vertex_array_proc      bind_vertex_array;
extern create_vertex_buffer_proc   create_vertex_buffer;
extern bind_vertex_buffer_proc     bind_vertex_buffer;
extern buffer_vertex_data_proc     buffer_vertex_data;
extern define_vertex_attrib_proc   define_vertex_attrib;
extern enable_vertex_attrib_proc   enable_vertex_attrib;
extern create_fbo_proc             create_fbo;
extern set_fbo_color_texture_proc  set_fbo_color_texture;
extern delete_fbo_proc             delete_fbo;
extern bind_fbo_proc               bind_fbo;
extern unbind_fbo_proc             unbind_fbo;
extern bind_texture_proc           bind_texture;
extern draw_data_proc              draw_data;
extern create_texture_proc         create_texture;
extern draw_elements_data_proc     draw_elements_data;

enum Graphics_API {
     OPENGL_GRAPHICS_API,
};

Rc_t load_graphics_api( Graphics_API graphics_api );

} // end namespace Engine

#endif //__PLATFORM_GRAPHICS_H__
