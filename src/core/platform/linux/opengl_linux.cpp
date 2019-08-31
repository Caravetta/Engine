#include <GL/glx.h>
#include "opengl_linux.h"

namespace Engine {
namespace OpenGL {

#define OPENGL_LOAD( func_name, func_define )                                                                 \
     func_name = (func_define)glXGetProcAddress((const GLubyte*)#func_name);                                  \
     if ( !func_name ) { LOG_ERROR("%s: Failed to load %s", __FUNCTION__, #func_name); return ENGINE_ERROR; }

glShaderSourceProc                 glShaderSource                = NULL;
glCreateShaderProc                 glCreateShader                = NULL;
glCompileShaderProc                glCompileShader               = NULL;
glGetShaderivProc                  glGetShaderiv                 = NULL;
glDeleteShaderProc                 glDeleteShader                = NULL;
glCreateProgramProc                glCreateProgram               = NULL;
glAttachShaderProc                 glAttachShader                = NULL;
glLinkProgramProc                  glLinkProgram                 = NULL;
glGetProgramivProc                 glGetProgramiv                = NULL;
glDeleteProgramProc                glDeleteProgram               = NULL;
glGenBuffersProc                   glGenBuffers                  = NULL;
glBindBufferProc                   glBindBuffer                  = NULL;
glBufferDataProc                   glBufferData                  = NULL;
glEnableVertexAttribArrayProc      glEnableVertexAttribArray     = NULL;
glDisableVertexAttribArrayProc     glDisableVertexAttribArray    = NULL;
glVertexAttribPointerProc          glVertexAttribPointer         = NULL;
glDrawArraysProc                   glDrawArrays                  = NULL;
glUseProgramProc                   glUseProgram                  = NULL;
glGenVertexArraysProc              glGenVertexArrays             = NULL;
glBindVertexArrayProc              glBindVertexArray             = NULL;
glUniform1fProc                    glUniform1f                   = NULL;
glUniform2fProc                    glUniform2f                   = NULL;
glUniform3fProc                    glUniform3f                   = NULL;
glUniform4fProc                    glUniform4f                   = NULL;
glUniformMatrix4fvProc             glUniformMatrix4fv            = NULL;
glGetUniformLocationProc           glGetUniformLocation          = NULL;

Rc_t init_opengl( void )
{
     //OPENGL_LOAD(glGenVertexArrays, glGenVertexArraysProc);
     OPENGL_LOAD(glShaderSource, glShaderSourceProc);
     OPENGL_LOAD(glCreateShader, glCreateShaderProc);
     OPENGL_LOAD(glCompileShader, glCompileShaderProc);
     OPENGL_LOAD(glGetShaderiv, glGetShaderivProc);
     OPENGL_LOAD(glDeleteShader, glDeleteShaderProc);
     OPENGL_LOAD(glCreateProgram, glCreateProgramProc);
     OPENGL_LOAD(glAttachShader, glAttachShaderProc);
     OPENGL_LOAD(glLinkProgram, glLinkProgramProc);
     OPENGL_LOAD(glGetProgramiv, glGetProgramivProc);
     OPENGL_LOAD(glDeleteProgram, glDeleteProgramProc);
     OPENGL_LOAD(glGenBuffers, glGenBuffersProc);
     OPENGL_LOAD(glBindBuffer, glBindBufferProc);
     OPENGL_LOAD(glBufferData, glBufferDataProc);
     OPENGL_LOAD(glEnableVertexAttribArray, glEnableVertexAttribArrayProc);
     OPENGL_LOAD(glDisableVertexAttribArray, glDisableVertexAttribArrayProc);
     OPENGL_LOAD(glVertexAttribPointer, glVertexAttribPointerProc);
     OPENGL_LOAD(glDrawArrays, glDrawArraysProc);
     OPENGL_LOAD(glUseProgram, glUseProgramProc);
     OPENGL_LOAD(glGenVertexArrays, glGenVertexArraysProc);
     OPENGL_LOAD(glBindVertexArray, glBindVertexArrayProc);
     OPENGL_LOAD(glUniform1f, glUniform1fProc);
     OPENGL_LOAD(glUniform2f, glUniform2fProc);
     OPENGL_LOAD(glUniform3f, glUniform3fProc);
     OPENGL_LOAD(glUniform4f, glUniform4fProc);
     OPENGL_LOAD(glUniformMatrix4fv, glUniformMatrix4fvProc);
     OPENGL_LOAD(glGetUniformLocation, glGetUniformLocationProc);

     return SUCCESS;
}

} // end namespace OpenGL
} // end namespace Engine

