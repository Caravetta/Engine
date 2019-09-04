#include "shader_gl.h"

#ifdef WINDOWS
#include "opengl_win32.h"
#elif LINUX
#include "opengl_linux.h"
#else
     #error
#endif

namespace Engine {

void* __shader_contents( const char *filename, GLint *length )
{
     FILE *f = fopen(filename, "r");
     void *buffer;

     if ( !f ) {
          LOG_ERROR("%s: Unable to open %s for reading", __FUNCTION__, filename);
          //fprintf(stderr, "Unable to open %s for reading\n", filename);
          return NULL;
     }

     fseek(f, 0, SEEK_END);
     *length = ftell(f);
     fseek(f, 0, SEEK_SET);

     buffer = malloc(*length + 1);
     *length = (OpenGL::GLint)fread(buffer, 1, *length, f);
     fclose(f);
     ((char*)buffer)[*length] = '\0';

     return buffer;
}

Shader_GL::Shader_GL( std::vector<Shader_GL_File> files )
{
     OpenGL::GLint is_ok;
     std::vector<OpenGL::GLuint> shader_ids;
     shader_ids.resize(files.size());

     for ( size_t ii = 0; ii < files.size(); ii++ ) {

          OpenGL::GLint length;
          OpenGL::GLchar* source = (OpenGL::GLchar *)__shader_contents(files[ii].file.c_str(), &length);
          if ( source == NULL ) {
               __id = -1;
               return;
          }

          //TODO(JOSH): need to parse the shader and gen the uniform locations

          shader_ids[ii] = OpenGL::glCreateShader(files[ii].type);
          if ( shader_ids[ii] == 0 ) {
               //TODO(JOSH): need tp clean up other shaders that where created
               LOG_ERROR("%s: Failed to create shader", __FUNCTION__);
               __id = -1;
               return;
          }

          OpenGL::glShaderSource(shader_ids[ii], 1, (const OpenGL::GLchar**)&source, &length);

          free(source);

          OpenGL::glCompileShader(shader_ids[ii]);

          OpenGL::glGetShaderiv(shader_ids[ii], GL_COMPILE_STATUS, &is_ok);
          if ( !is_ok ) {
               LOG_ERROR("%s: Failed to load shader %s", __FUNCTION__, files[ii].file.c_str());
               //TODO(JOSH): need tp clean up other shaders that where created
               OpenGL::glDeleteShader(shader_ids[ii]);
               __id = -1;
               return;
          }
     }

     __id = OpenGL::glCreateProgram();

     for ( size_t ii = 0; ii < shader_ids.size(); ii++ ) {
          OpenGL::glAttachShader(__id, shader_ids[ii]);
     }

     OpenGL::glLinkProgram(__id);
     OpenGL::glGetProgramiv(__id, GL_LINK_STATUS, &is_ok);
     if ( !is_ok ) {
          LOG_ERROR("%s: Error creating program", __FUNCTION__);
          OpenGL::glDeleteProgram(__id);
          __id = -1;
          return;
     }
}

Shader_GL::Shader_GL( std::vector<Shader_GL_String> strings )
{
     OpenGL::GLint is_ok;
     std::vector<OpenGL::GLuint> shader_ids;
     shader_ids.resize(strings.size());
     LOG("size %zd", strings.size());
     for ( size_t ii = 0; ii < strings.size(); ii++ ) {

          OpenGL::GLint length = strings[ii].length;
          LOG("JOSH Length %d", length);
          OpenGL::GLchar* source = (OpenGL::GLchar *)strings[ii].source;
          if ( source == NULL ) {
               __id = -1;
               return;
          }

          //TODO(JOSH): need to parse the shader and gen the uniform locations

          shader_ids[ii] = OpenGL::glCreateShader(strings[ii].type);
          if ( shader_ids[ii] == 0 ) {
               //TODO(JOSH): need tp clean up other shaders that where created
               LOG_ERROR("%s: Failed to create shader", __FUNCTION__);
               __id = -1;
               return;
          }

          OpenGL::glShaderSource(shader_ids[ii], 1, (const OpenGL::GLchar**)&source, &length);

          OpenGL::glCompileShader(shader_ids[ii]);

          OpenGL::glGetShaderiv(shader_ids[ii], GL_COMPILE_STATUS, &is_ok);
          if ( !is_ok ) {
               LOG_ERROR("%s: Failed to load shader", __FUNCTION__);
               //TODO(JOSH): need tp clean up other shaders that where created
               OpenGL::glDeleteShader(shader_ids[ii]);
               __id = -1;
               return;
          }
     }

     __id = OpenGL::glCreateProgram();

     for ( size_t ii = 0; ii < shader_ids.size(); ii++ ) {
          OpenGL::glAttachShader(__id, shader_ids[ii]);
     }

     OpenGL::glLinkProgram(__id);
     OpenGL::glGetProgramiv(__id, GL_LINK_STATUS, &is_ok);
     if ( !is_ok ) {
          LOG_ERROR("%s: Error creating program", __FUNCTION__);
          OpenGL::glDeleteProgram(__id);
          __id = -1;
          return;
     }

}

int32_t Shader_GL::id( void )
{
     return __id;
}

int32_t Shader_GL::uniform_id( std::string name )
{
     return OpenGL::glGetUniformLocation(__id, name.c_str());
}

void Shader_GL::set_uniform_float1( int32_t location, float value )
{
     OpenGL::glUniform1f(location, value);
}

void Shader_GL::set_uniform_float2( int32_t location, float value_1, float value_2 )
{
     OpenGL::glUniform2f(location, value_1, value_2);
}

void Shader_GL::set_uniform_float3( int32_t location, float value_1, float value_2, float value_3 )
{
     OpenGL::glUniform3f(location, value_1, value_2, value_3);
}

void Shader_GL::set_uniform_float4( int32_t location, float value_1, float value_2, float value_3, float value_4 )
{
     OpenGL::glUniform4f(location, value_1, value_2, value_3, value_4);
}

void Shader_GL::set_uniform_mat4( int32_t location, Matrix4f* matrix )
{
     OpenGL::glUniformMatrix4fv(location, 1, GL_FALSE, (float*)&matrix->x);
}

} // end namespace Engine

