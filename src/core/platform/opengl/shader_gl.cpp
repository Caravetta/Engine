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

          shader_ids[ii] = OpenGL::glCreateShader(files[ii].type);
          OpenGL::glShaderSource(shader_ids[ii], 1, (const OpenGL::GLchar**)&source, &length);

          free(source);

          OpenGL::glCompileShader(shader_ids[ii]);

          OpenGL::glGetShaderiv(shader_ids[ii], GL_COMPILE_STATUS, &is_ok);
          if ( !is_ok ) {
               LOG_ERROR("%s: Error loading shader %s", __FUNCTION__, files[ii].file.c_str());
               //TODO(JOSH): need tp clean up other shaders
               OpenGL::glDeleteShader(shader_ids[ii]);
               __id = -1;
               return;
          }
     }

     __id = OpenGL::glCreateProgram();

     for ( size_t ii = 0; ii < shader_ids.size(); ii++ ) {
          LOG("Linking %d to %d", shader_ids[ii], __id);
          OpenGL::glAttachShader(__id, shader_ids[ii]);
     }

     OpenGL::glLinkProgram(__id);
     LOG("HEREEEEEEEEEEE");
     OpenGL::glGetProgramiv(__id, GL_LINK_STATUS, &is_ok);
     if ( !is_ok ) {
          LOG_ERROR("%s: Error creating program", __FUNCTION__);
          OpenGL::glDeleteProgram(__id);
          __id = -1;
          return;
     }
}

unsigned int Shader_GL::id( void )
{
     return __id;
}

} // end namespace Engine

