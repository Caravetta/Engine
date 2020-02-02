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

#define GL_DEPTH_STENCIL 0x84F9
#define GL_DEPTH_STENCIL_ATTACHMENT 0x821A

GLenum type_array[] = {
     GL_FLOAT,
     GL_UNSIGNED_BYTE,
     GL_UNSIGNED_SHORT,
     GL_UNSIGNED_INT,
     GL_UNSIGNED_INT_24_8,
};

GLenum usage_type[] = {
     GL_STATIC_DRAW,
     GL_STREAM_DRAW,
};

GLenum draw_mode[] = {
     GL_TRIANGLES,
};

GLenum depth_func_array[] = {
     GL_LESS,
};

GLenum options_array[] = {
     GL_DEPTH_TEST,
     GL_BLEND,
     GL_CULL_FACE,
     GL_SCISSOR_TEST,
};

GLenum buffer_types[] = {
     GL_ELEMENT_ARRAY_BUFFER,
     GL_ARRAY_BUFFER,
};

GLenum texture_format[] = {
     GL_RGB,
     GL_RGBA,
     GL_RGB16F,
     GL_DEPTH24_STENCIL8,
     GL_DEPTH_STENCIL,
};

GLenum attachments_type[] = {
     GL_COLOR_ATTACHMENT0,
     GL_COLOR_ATTACHMENT1,
     GL_COLOR_ATTACHMENT2,
     GL_DEPTH_STENCIL_ATTACHMENT,
};

GLenum texture_unit_array[] = {
     GL_TEXTURE0,
     GL_TEXTURE1,
     GL_TEXTURE2,
     GL_TEXTURE3,
};

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
     glClearColor(r, g, b, a);
}

extern "C" void graphics_clear( uint64_t clear_mask )
{
     glEnable(GL_CULL_FACE);
     glCullFace(GL_BACK);
     glFrontFace(GL_CCW);
     GLbitfield mask = 0;

     mask |= (clear_mask & COLOR_BUFFER_CLEAR) ? GL_COLOR_BUFFER_BIT : 0;
     mask |= (clear_mask & DEPTH_BUFFER_CLEAR) ? GL_DEPTH_BUFFER_BIT : 0;
     mask |= (clear_mask & ACCUM_BUFFER_CLEAR) ? GL_ACCUM_BUFFER_BIT : 0;

     glClear(mask);
}

extern "C" void set_view_port( int x, int y, size_t width, size_t height )
{
     glViewport(x, y, (GLsizei)width, (GLsizei)height);
}

extern "C" void enable_graphics_option( Graphics_Option option )
{
     glEnable(options_array[option]);

     if ( option == BLEND_OPTION ) {
#ifdef LINUX
          glBlendEquation(GL_FUNC_ADD);
#elif WINDOWS
          OpenGL::glBlendEquation(GL_FUNC_ADD);
#endif
          glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
     }
}

extern "C" void disable_graphics_option( Graphics_Option option )
{
     glDisable(options_array[option]);
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
               GLint maxLength = 0;
	          OpenGL::glGetShaderiv(shader_ids[ii], GL_INFO_LOG_LENGTH, &maxLength);
               std::vector<char> errorLog(maxLength);
               OpenGL::glGetShaderInfoLog(shader_ids[ii], maxLength, &maxLength, &errorLog[0]);
               LOG("%s", (char*)errorLog.data());
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
          //glColorMask(false, false, false, false);
          //glDepthMask(GL_TRUE);
          //glDepthFunc(GL_LESS);
          //glEnable(GL_DEPTH_TEST);
          //glClear(GL_DEPTH_BUFFER_BIT);
     OpenGL::glUseProgram(program_id);
}

extern "C" int32_t fetch_attrib_id( int32_t program_id, uint8_t* name )
{
     return OpenGL::glGetAttribLocation(program_id, ((std::string*)name)->c_str());;
}

extern "C" int32_t fetch_uniform_id( int32_t program_id, uint8_t* name )
{
     return OpenGL::glGetUniformLocation(program_id, ((std::string*)name)->c_str());;
}

extern "C" void upload_uniform_int1( int32_t location, int value )
{
     OpenGL::glUniform1i(location, value);
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

extern "C" void bind_vertex_buffer( Buffer_Type type, uint32_t buffer_id )
{
     OpenGL::glBindBuffer(buffer_types[type], buffer_id);
}

extern "C" void buffer_vertex_data( Buffer_Type type, uint8_t* data, size_t size, Usage_Type usage )
{
     OpenGL::glBufferData(buffer_types[type], size, data, usage_type[usage]);
}

extern "C" void define_vertex_attrib( uint32_t index, size_t size, bool normalized,
                                      Data_Type type, size_t stride, uint8_t* data )
{
     OpenGL::glVertexAttribPointer(index, (GLsizei)size, type_array[type],
                                   (normalized == true ? GL_TRUE : GL_FALSE),
                                   (GLsizei)stride, (void*)data);
}

extern "C" void enable_vertex_attrib( uint32_t index )
{
     OpenGL::glEnableVertexAttribArray(index);
}

extern "C" Texture_Handle create_texture( int width, int height, uint8_t* data, Texture_Format internal_format,
                                          Texture_Format format, Data_Type type )
{
     Texture_Handle handle;

     OpenGL::glGenTextures(1, &handle);
     OpenGL::glBindTexture(GL_TEXTURE_2D, handle);

#ifdef LINUX
     OpenGL::glTexImage2D(GL_TEXTURE_2D, 0, texture_format[internal_format], width, height,
                          0, texture_format[format], type_array[type], data);
     OpenGL::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
     OpenGL::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
#elif WINDOWS
     glTexImage2D(GL_TEXTURE_2D, 0, texture_format[internal_format], width, height,
                  0, texture_format[format], type_array[type], data);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
#endif

     OpenGL::glBindTexture(GL_TEXTURE_2D, 0);


     return handle;
}

Engine::OpenGL::GLuint rbo;
extern "C" Fbo_Handle create_fbo( void )
{
     Fbo_Handle handle;

     OpenGL::glGenFramebuffers(1, (unsigned int*)&handle);
#if 0
     OpenGL::glBindFramebuffer(GL_FRAMEBUFFER, data->framebuffer);
     OpenGL::glGenTextures(1, &data->texColorBuffer);
     OpenGL::glBindTexture(GL_TEXTURE_2D, data->texColorBuffer);
     OpenGL::glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height,
                          0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
     OpenGL::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
     OpenGL::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
     OpenGL::glBindTexture(GL_TEXTURE_2D, 0);

     OpenGL::glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                                    GL_TEXTURE_2D, data->texColorBuffer, 0);

     if ( add_depth ) {
          OpenGL::glGenTextures(1, &data->texDepth);
          OpenGL::glBindTexture(GL_TEXTURE_2D, data->texDepth);
          OpenGL::glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, width, height,
                               0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
          OpenGL::glBindTexture(GL_TEXTURE_2D, 0);
          OpenGL::glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
                                         GL_TEXTURE_2D, data->texDepth, 0);
     }

     OpenGL::glBindFramebuffer(GL_FRAMEBUFFER, 0);
#endif
#if 0
          OpenGL::glBindFramebuffer(GL_FRAMEBUFFER, handle);
          OpenGL::glGenTextures(1, &rbo);
          OpenGL::glBindTexture(GL_TEXTURE_2D, rbo);
          OpenGL::glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, 800, 600,
                               0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
          OpenGL::glBindTexture(GL_TEXTURE_2D, 0);
          OpenGL::glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
                                         GL_TEXTURE_2D, rbo, 0);
     OpenGL::glBindFramebuffer(GL_FRAMEBUFFER, 0);
#endif
     OpenGL::glBindFramebuffer(GL_FRAMEBUFFER, 0);
     return handle;
}

extern "C" void set_fbo_color_texture( int color_texture, Attachment_Type attachment )
{
     OpenGL::glFramebufferTexture2D(GL_FRAMEBUFFER, attachments_type[attachment],
                                    GL_TEXTURE_2D, color_texture, 0);
}

extern "C" void delete_fbo( Fbo_Handle fbo )
{

}

extern "C" void bind_fbo( Fbo_Handle fbo )
{
     OpenGL::glBindFramebuffer(GL_FRAMEBUFFER, (unsigned int)fbo);
}

extern "C" void unbind_fbo( void )
{
     OpenGL::glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

extern "C" void bind_texture( Texture_Unit unit, int texture_id )
{
#ifdef LINUX
     glActiveTexture(texture_unit_array[unit]);
#elif WINDOWS
     OpenGL::glActiveTexture(texture_unit_array[unit]);
#endif
     glBindTexture(GL_TEXTURE_2D, texture_id);
}

extern "C" void draw_data( Draw_Mode mode, int first, size_t count )
{
     OpenGL::glDrawArrays(draw_mode[mode], first, (GLsizei)count);
}

extern "C" void draw_elements_data( Draw_Mode mode, size_t count, Data_Type type, void* offset )
{
     OpenGL::glDrawElements(draw_mode[mode], (GLsizei)count, type_array[type], offset);
}

extern "C" void scissor_box( int x, int y, size_t width, size_t height )
{
#ifdef LINUX
     OpenGL::glScissor(x, y, width, height);
#elif WINDOWS
     glScissor(x, y, (GLsizei)width, (GLsizei)height);
#endif
}

extern "C" void delete_texture( Texture_Handle handle )
{
#ifdef LINUX
#elif WINDOWS
     glDeleteTextures(1, &handle);
#endif
}

extern "C" void set_draw_buffers( Attachment_Type* attachments, size_t n_attachments )
{
     unsigned int attachments_list[10];

     for ( size_t ii = 0; ii < n_attachments; ii++ ) {
          attachments_list[ii] = attachments_type[attachments[ii]];
     }

     OpenGL::glDrawBuffers(n_attachments, attachments_list);
}

} // end namespace Engine

