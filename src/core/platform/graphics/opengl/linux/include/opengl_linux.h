#ifndef __OPENGL_LINUX_H__
#define __OPENGL_LINUX_H__

#include <GL/gl.h>
#include "core_common.h"
#include "opengl_common.h"

namespace Engine {
namespace OpenGL {

typedef void (*glShaderSourceProc) ( GLuint shader, GLsizei count, const char* *string, const GLint *length );
typedef GLuint (*glCreateShaderProc) ( GLenum type );
typedef void (*glCompileShaderProc) ( GLuint shader );
typedef void (*glGetShaderivProc) ( GLuint shader, GLenum pname, GLint *params );
typedef void (*glGetShaderInfoLogProc) ( GLuint shader, GLsizei maxLength, GLsizei *length, GLchar *infoLog );
typedef void (*glDeleteShaderProc) ( GLuint shader );
typedef GLuint (*glCreateProgramProc) ( void );
typedef void (*glAttachShaderProc) ( GLuint program, GLuint shader );
typedef void (*glLinkProgramProc) ( GLuint program );
typedef void (*glGetProgramivProc) ( GLuint program, GLenum pname, GLint *params );
typedef void (*glDeleteProgramProc) ( GLuint program );
typedef void (*glGenBuffersProc) ( GLsizei n, GLuint *buffers );
typedef void (*glBindBufferProc) ( GLenum target, GLuint buffer );
typedef void (*glBufferDataProc) ( GLenum target, ptrdiff_t size, const GLvoid *data, GLenum usage );
typedef void (*glEnableVertexAttribArrayProc) ( GLuint index );
typedef void (*glDisableVertexAttribArrayProc) ( GLuint index );
typedef void (*glVertexAttribPointerProc) ( GLuint index, GLint size, GLenum type,
                                            GLboolean normalized, GLsizei stride, const GLvoid *pointer );
typedef void (*glDrawArraysProc) ( GLenum mode, GLint first, GLsizei count );
typedef void (*glUseProgramProc) ( GLuint program );
typedef void (*glGenVertexArraysProc) ( GLsizei n, GLuint* arrays );
typedef void (*glBindVertexArrayProc) ( GLuint array );
typedef void (*glUniform1iProc) ( GLint location, GLint v0 );
typedef void (*glUniform1fProc) ( GLint location, GLfloat v0 );
typedef void (*glUniform2fProc) ( GLint location, GLfloat v0, GLfloat v1 );
typedef void (*glUniform3fProc) ( GLint location, GLfloat v0, GLfloat v1, GLfloat v2 );
typedef void (*glUniform4fProc) ( GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3 );
typedef void (*glUniformMatrix4fvProc) ( GLint location, GLsizei count, GLboolean transpose, const GLfloat* value );
typedef GLint (*glGetUniformLocationProc) ( GLuint program, const GLchar* name );

typedef void (*glGenFramebuffersProc) ( GLsizei n, GLuint* ids );
typedef void (*glBindFramebufferProc) ( GLenum target, GLuint framebuffer );
typedef GLenum (*glCheckNamedFramebufferStatusProc) ( GLuint framebuffer, GLenum target );
typedef void (*glDeleteFramebuffersProc) ( GLsizei n, GLuint* framebuffers );
typedef void (*glGenTexturesProc) ( GLsizei n, GLuint* textures );
typedef void (*glBindTextureProc) ( GLenum target, GLuint texture );
typedef void (*glTexImage2DProc) ( GLenum target, GLint level, GLint internalformat,
                                   GLsizei width, GLsizei height, GLint border,
                                   GLenum format, GLenum type, const GLvoid* data);
typedef void (*glTexParameteriProc) ( GLenum target, GLenum pname, GLint param );
typedef void (*glFramebufferTexture2DProc) ( GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level );
typedef void (*glDrawElementsProc) ( GLenum mode, GLsizei count, GLenum type, const GLvoid * indices);

extern glShaderSourceProc                    glShaderSource;
extern glCreateShaderProc                    glCreateShader;
extern glCompileShaderProc                   glCompileShader;
extern glGetShaderivProc                     glGetShaderiv;
extern glGetShaderInfoLogProc                glGetShaderInfoLog;
extern glDeleteShaderProc                    glDeleteShader;
extern glCreateProgramProc                   glCreateProgram;
extern glAttachShaderProc                    glAttachShader;
extern glLinkProgramProc                     glLinkProgram;
extern glGetProgramivProc                    glGetProgramiv;
extern glDeleteProgramProc                   glDeleteProgram;
extern glGenBuffersProc                      glGenBuffers;
extern glBindBufferProc                      glBindBuffer;
extern glBufferDataProc                      glBufferData;
extern glEnableVertexAttribArrayProc         glEnableVertexAttribArray;
extern glDisableVertexAttribArrayProc        glDisableVertexAttribArray;
extern glVertexAttribPointerProc             glVertexAttribPointer;
extern glDrawArraysProc                      glDrawArrays;
extern glUseProgramProc                      glUseProgram;
extern glGenVertexArraysProc                 glGenVertexArrays;
extern glBindVertexArrayProc                 glBindVertexArray;
extern glUniform1iProc                       glUniform1i;
extern glUniform1fProc                       glUniform1f;
extern glUniform2fProc                       glUniform2f;
extern glUniform3fProc                       glUniform3f;
extern glUniform4fProc                       glUniform4f;
extern glUniformMatrix4fvProc                glUniformMatrix4fv;
extern glGetUniformLocationProc              glGetUniformLocation;

extern glGenFramebuffersProc                 glGenFramebuffers;
extern glBindFramebufferProc                 glBindFramebuffer;
extern glCheckNamedFramebufferStatusProc     glCheckNamedFramebufferStatus;
extern glDeleteFramebuffersProc              glDeleteFramebuffers;
extern glGenTexturesProc                     glGenTextures;
extern glBindTextureProc                     glBindTexture;
extern glTexImage2DProc                      glTexImage2D;
extern glTexParameteriProc                   glTexParameteri;
extern glFramebufferTexture2DProc            glFramebufferTexture2D;
extern glDrawElementsProc                    glDrawElements;

Rc_t init_opengl( void );

} // end namespace OpenGL

Rc_t init_render_context( struct platform_window_t* window );
void buffer_swap( struct platform_window_t* window );

} // end namespace Engine

#endif //__OPENGL_LINUX_H__
