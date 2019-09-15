#include <vector>
#include <string>
#include "opengl_platform.h"
#include "matrix4f.h"
#include "shader_common.h"

#ifdef WINDOWS
     #include "opengl_win32.h"
#elif LINUX
     #include "opengl_linux.h"
#else
     #error
#endif

namespace Engine {

GLenum type_array[] = {
     GL_FLOAT,
};

GLenum draw_mode[] = {
     GL_TRIANGLES,
};

GLenum depth_func_array[] = {
     GL_LESS,
};

GLenum options_array[] = {
     GL_DEPTH_TEST,
};

unsigned int framebuffer;
unsigned int texColorBuffer;
unsigned int texDepth;

extern "C" Rc_t init_graphics_platform( void )
{
     return OpenGL::init_opengl();
}

extern "C" Rc_t create_render_context( struct platform_window_t* window )
{
     return init_render_context(window);
}

extern "C" void swap_buffer( struct platform_window_t* window )
{
     buffer_swap(window);
}

extern "C" void set_clear_color( float r, float g, float b, float a )
{
#if 0
     OpenGL::glGenFramebuffers(1, &framebuffer);
     OpenGL::glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

     OpenGL::glGenTextures(1, &texColorBuffer);
     OpenGL::glBindTexture(GL_TEXTURE_2D, texColorBuffer);
     OpenGL::glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
     OpenGL::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
     OpenGL::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
     OpenGL::glBindTexture(GL_TEXTURE_2D, 0);
     // attach it to currently bound framebuffer object
     OpenGL::glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColorBuffer, 0);
#endif

     glClearColor(r, g, b, a);
}

extern "C" void graphics_clear( uint64_t clear_mask )
{
     GLbitfield mask = 0;

     mask |= (clear_mask & COLOR_BUFFER_CLEAR) ? GL_COLOR_BUFFER_BIT : 0;
     mask |= (clear_mask & DEPTH_BUFFER_CLEAR) ? GL_DEPTH_BUFFER_BIT : 0;

     glClear(mask);
}

extern "C" void set_view_port( int x, int y, size_t width, size_t height )
{
     glViewport(x, y, width, height);
}

extern "C" void enable_graphics_option( Graphics_Option option )
{
     glEnable(options_array[option]);
}

extern "C" void set_depth_func( Depth_Func type )
{
     glDepthFunc(depth_func_array[type]);
}

extern "C" int32_t create_program_file( uint8_t* files )
{
     return 0;
}

extern "C" int32_t create_program_string( uint8_t* strings )
{
     int32_t id;

     std::vector<Shader_String>* p_strings = (std::vector<Shader_String>*)strings;

     OpenGL::GLint is_ok;
     std::vector<OpenGL::GLuint> shader_ids;
     shader_ids.resize(p_strings->size());

     for ( size_t ii = 0; ii < p_strings->size(); ii++ ) {

          OpenGL::GLint length = (GLint)p_strings->at(ii).length;
          OpenGL::GLchar* source = (OpenGL::GLchar *)p_strings->at(ii).source;
          if ( source == NULL ) {
               id = -1;
               return id;
          }

          //TODO(JOSH): need to parse the shader and gen the uniform locations

          shader_ids[ii] = OpenGL::glCreateShader(p_strings->at(ii).type);
          if ( shader_ids[ii] == 0 ) {
               //TODO(JOSH): need tp clean up other shaders that where created
               LOG_ERROR("%s: Failed to create shader", __FUNCTION__);
               id = -1;
               return id;
          }

          OpenGL::glShaderSource(shader_ids[ii], 1, (const OpenGL::GLchar**)&source, &length);

          OpenGL::glCompileShader(shader_ids[ii]);

          OpenGL::glGetShaderiv(shader_ids[ii], GL_COMPILE_STATUS, &is_ok);
          if ( !is_ok ) {
               LOG_ERROR("%s: Failed to load shader", __FUNCTION__);
               //TODO(JOSH): need tp clean up other shaders that where created
               OpenGL::glDeleteShader(shader_ids[ii]);
               id = -1;
               return id;
          }
     }

     id = OpenGL::glCreateProgram();

     for ( size_t ii = 0; ii < shader_ids.size(); ii++ ) {
          OpenGL::glAttachShader(id, shader_ids[ii]);
     }

     OpenGL::glLinkProgram(id);
     OpenGL::glGetProgramiv(id, GL_LINK_STATUS, &is_ok);
     if ( !is_ok ) {
          LOG_ERROR("%s: Error creating program", __FUNCTION__);
          OpenGL::glDeleteProgram(id);
          id = -1;
          return id;
     }

     return id;
}

extern "C" void use_program( int32_t program_id )
{
     OpenGL::glUseProgram(program_id);
}

extern "C" int32_t fetch_uniform_id( int32_t program_id, uint8_t* name )
{
     return OpenGL::glGetUniformLocation(program_id, ((std::string*)name)->c_str());;
}

extern "C" void upload_uniform_float1( int32_t location, float value )
{
     OpenGL::glUniform1f(location, value);
}

extern "C" void upload_uniform_float2( int32_t location, float value_1, float value_2 )
{
     OpenGL::glUniform2f(location, value_1, value_2);
}

extern "C" void upload_uniform_float3( int32_t location, float value_1, float value_2, float value_3 )
{
     OpenGL::glUniform3f(location, value_1, value_2, value_3);
}

extern "C" void upload_uniform_float4( int32_t location, float value_1, float value_2, float value_3, float value_4 )
{
     OpenGL::glUniform4f(location, value_1, value_2, value_3, value_4);
}

extern "C" void upload_uniform_mat4( int32_t location, uint8_t* matrix )
{
     Matrix4f* mat = (Matrix4f*)matrix;
     OpenGL::glUniformMatrix4fv(location, 1, GL_FALSE, (float*)&mat->x);
}

extern "C" uint32_t create_vertex_array( void )
{
     uint32_t id;
     OpenGL::glGenVertexArrays(1, &id);
     return id;
}

extern "C" void bind_vertex_array( uint32_t array_id )
{
     OpenGL::glBindVertexArray(array_id);
}

extern "C" uint32_t create_vertex_buffer( void )
{
     uint32_t id;
     OpenGL::glGenBuffers(1, &id);
     return id;
}

extern "C" void bind_vertex_buffer( uint32_t buffer_id )
{
     OpenGL::glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
}

extern "C" void buffer_vertex_data( uint8_t* data, size_t size )
{
     OpenGL::glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

extern "C" void define_vertex_attrib( uint32_t index, size_t size, Data_Type type, size_t stride, uint8_t* data )
{
     OpenGL::glVertexAttribPointer(index, size, type_array[type], GL_FALSE, stride, (void*)data);
}

extern "C" void enable_vertex_attrib( uint32_t index )
{
     OpenGL::glEnableVertexAttribArray(index);
}

extern "C" void draw_data( Draw_Mode mode, int first, size_t count )
{
     OpenGL::glDrawArrays(draw_mode[mode], first, count);
}

} // end namespace Engine

