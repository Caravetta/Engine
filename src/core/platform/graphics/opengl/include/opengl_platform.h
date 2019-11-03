#ifndef __OPENGL_PLATFORM_H__
#define __OPENGL_PLATFORM_H__

#include "core_common.h"
#include "platform_graphics_common.h"

namespace Engine {

extern "C" GRAPHICS_API Rc_t init_graphics_platform( void );

extern "C" GRAPHICS_API Rc_t create_render_context( struct platform_window_t* window );
extern "C" GRAPHICS_API void swap_buffer( struct platform_window_t* window );

extern "C" GRAPHICS_API void set_clear_color( float r, float g, float b, float a );
extern "C" GRAPHICS_API void graphics_clear( uint64_t clear_mask );
extern "C" GRAPHICS_API void set_view_port( int x, int y, size_t width, size_t height );
extern "C" GRAPHICS_API void enable_graphics_option( Graphics_Option option );
extern "C" GRAPHICS_API void disable_graphics_option( Graphics_Option option );
extern "C" GRAPHICS_API void set_depth_func( Depth_Func type );

extern "C" GRAPHICS_API int32_t create_program_file( uint8_t* files );
extern "C" GRAPHICS_API int32_t create_program_string( uint8_t* strings );
extern "C" GRAPHICS_API void use_program( int32_t program_id );
extern "C" GRAPHICS_API int32_t fetch_attrib_id( int32_t program_id, uint8_t* name );
extern "C" GRAPHICS_API int32_t fetch_uniform_id( int32_t program_id, uint8_t* name );
extern "C" GRAPHICS_API void upload_uniform_int1( int32_t location, int value );
extern "C" GRAPHICS_API void upload_uniform_float1( int32_t location, float value );
extern "C" GRAPHICS_API void upload_uniform_float2( int32_t location, float value_1, float value_2 );
extern "C" GRAPHICS_API void upload_uniform_float3( int32_t location, float value_1, float value_2, float value_3 );
extern "C" GRAPHICS_API void upload_uniform_float4( int32_t location, float value_1, float value_2, float value_3, float value_4 );
extern "C" GRAPHICS_API void upload_uniform_mat4( int32_t location, uint8_t* matrix );

extern "C" GRAPHICS_API uint32_t create_vertex_array( void );
extern "C" GRAPHICS_API void bind_vertex_array( uint32_t array_id );

extern "C" GRAPHICS_API uint32_t create_vertex_buffer( void );
extern "C" GRAPHICS_API void bind_vertex_buffer( Buffer_Type type, uint32_t buffer_id );
extern "C" GRAPHICS_API void buffer_vertex_data( Buffer_Type type, uint8_t* data, size_t size, Usage_Type usage );
extern "C" GRAPHICS_API void define_vertex_attrib( uint32_t index, size_t size, bool normalized, Data_Type type, size_t stride, uint8_t* data );
extern "C" GRAPHICS_API void enable_vertex_attrib( uint32_t index );

extern "C" GRAPHICS_API Texture_Handle create_texture( int width, int height, uint8_t* data, Texture_Format format );
extern "C" GRAPHICS_API void delete_texture( Texture_Handle handle );

extern "C" GRAPHICS_API Fbo_Handle create_fbo( void );
extern "C" GRAPHICS_API void set_fbo_color_texture( int color_texture );
extern "C" GRAPHICS_API void delete_fbo( Fbo_Handle fbo );
extern "C" GRAPHICS_API void bind_fbo( Fbo_Handle fbo );
extern "C" GRAPHICS_API void unbind_fbo( void );

extern "C" GRAPHICS_API void bind_texture( int texture_id );

extern "C" GRAPHICS_API void draw_data( Draw_Mode mode, int first, size_t count );
extern "C" GRAPHICS_API void draw_elements_data( Draw_Mode mode, size_t count, Data_Type type, void* offset );
extern "C" GRAPHICS_API void scissor_box( int x, int y, size_t width, size_t height );

} // end namespace Engine

#endif //__OPENGL_PLATFORM_H__
