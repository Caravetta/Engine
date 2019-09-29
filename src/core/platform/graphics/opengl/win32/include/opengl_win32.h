#ifndef __OPENGL_WIN32_H__
#define __OPENGL_WIN32_H__

#include <windows.h>
#include <gl/gl.h>
#include "core_common.h"
#include "opengl_common.h"

namespace Engine {
namespace OpenGL {

typedef HGLRC(WINAPI * PFNWGLCREATECONTEXTATTRIBSARBPROC) ( HDC hDC, HGLRC hShareContext, const int *attribList );
typedef BOOL(WINAPI * PFNWGLCHOOSEPIXELFORMATARBPROC) ( HDC hdc, const int *piAttribIList, const FLOAT *pfAttribFList,
                                                        UINT nMaxFormats, int *piFormats, UINT *nNumFormats );
typedef void (APIENTRY * PFNGLSHADERSOURCEPROC) ( GLuint shader, GLsizei count, const char* *string, const GLint *length );
typedef GLuint(APIENTRY * PFNGLCREATESHADERPROC) ( GLenum type );
typedef void (APIENTRY * PFNGLCOMPILESHADERPROC) ( GLuint shader );
typedef void (APIENTRY * PFNGLGETSHADERIVPROC) ( GLuint shader, GLenum pname, GLint *params );
typedef void (APIENTRY * PFNGLDELETESHADERPROC) ( GLuint shader );
typedef GLuint(APIENTRY * PFNGLCREATEPROGRAMPROC) ( void );
typedef void (APIENTRY * PFNGLATTACHSHADERPROC) ( GLuint program, GLuint shader );
typedef void (APIENTRY * PFNGLLINKPROGRAMPROC) ( GLuint program );
typedef void (APIENTRY * PFNGLGETPROGRAMIVPROC) ( GLuint program, GLenum pname, GLint *params );
typedef void (APIENTRY * PFNGLDELETEPROGRAMPROC) ( GLuint program );
typedef void (APIENTRY * PFNGLGENBUFFERSPROC) ( GLsizei n, GLuint *buffers );
typedef void (APIENTRY * PFNGLBINDBUFFERPROC) ( GLenum target, GLuint buffer );
typedef void (APIENTRY * PFNGLBUFFERDATAPROC) ( GLenum target, ptrdiff_t size, const GLvoid *data, GLenum usage );
typedef void (APIENTRY * PFNGLENABLEVERTEXATTRIBARRAYPROC) ( GLuint index );
typedef void (APIENTRY * PFNGLDISABLEVERTEXATTRIBARRAYPROC) ( GLuint index );
typedef void (APIENTRY * PFNGLVERTEXATTRIBPOINTERPROC) ( GLuint index, GLint size, GLenum type,
                                                         GLboolean normalized, GLsizei stride, const GLvoid *pointer );
typedef void (APIENTRY * PFNGLDRAWARRAYSPROC) ( GLenum mode, GLint first, GLsizei count );
typedef void (APIENTRY * PFNGLUSEPROGRAMPROC) ( GLuint program );
typedef void (APIENTRY * PFNGLGENVERTEXARRAYPROC) ( GLsizei n, GLuint* arrays );
typedef void (APIENTRY * PFNGLBINDVERTEXARRAYPROC) ( GLuint array );
typedef void (APIENTRY * PFNGLUNIFORM1FPROC) ( GLint location, GLfloat v0 );
typedef void (APIENTRY * PFNGLUNIFORM2FPROC) ( GLint location, GLfloat v0, GLfloat v1 );
typedef void (APIENTRY * PFNGLUNIFORM3FPROC) ( GLint location, GLfloat v0, GLfloat v1, GLfloat v2 );
typedef void (APIENTRY * PFNGLUNIFORM4FPROC) ( GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3 );
typedef void (APIENTRY * PFNGLUNIFORMMATRIX4FVPROC) ( GLint location, GLsizei count, GLboolean transpose, const GLfloat* value );
typedef GLint (APIENTRY * PFNGLGETUNIFORMLOCATIONPROC) ( GLuint program, const GLchar* name );

typedef void (APIENTRY * PFNGLGENFRAMEBUFFERSPROC) ( GLsizei n, GLuint* ids );
typedef void (APIENTRY * PFNGLBINDFRAMEBUFFERPROC) ( GLenum target, GLuint framebuffer );
typedef GLenum (APIENTRY * PFNGLCHECKNAMEDFRAMEBUFFERSTATUSPROC) ( GLuint framebuffer, GLenum target );
typedef void (APIENTRY * PFNGLDELETEFRAMEBUFFERSPROC) ( GLsizei n, GLuint* framebuffers );
typedef void (APIENTRY * PFNGLGENTEXTURESPROC) ( GLsizei n, GLuint* textures );
typedef void (APIENTRY * PFNGLBINDTEXTUREPROC) ( GLenum target, GLuint texture );
typedef void (APIENTRY * PFNGLTEXIMAGE2DPROC) ( GLenum target, GLint level, GLint internalformat,
                                                GLsizei width, GLsizei height, GLint border,
                                                 GLenum format, GLenum type, const GLvoid* data );
typedef void (APIENTRY * PFNGLTEXPARAMETERIPROC) ( GLenum target, GLenum pname, GLint param );
typedef void (APIENTRY * PFNGLFRAMEBUFFERTEXTURE2DPROC) ( GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level );


extern PFNWGLCREATECONTEXTATTRIBSARBPROC     wglCreateContextAttribsARB;
extern PFNWGLCHOOSEPIXELFORMATARBPROC        wglChoosePixelFormatARB;
extern PFNGLSHADERSOURCEPROC                 glShaderSource;
extern PFNGLCREATESHADERPROC                 glCreateShader;
extern PFNGLCOMPILESHADERPROC                glCompileShader;
extern PFNGLGETSHADERIVPROC                  glGetShaderiv;
extern PFNGLDELETESHADERPROC                 glDeleteShader;
extern PFNGLCREATEPROGRAMPROC                glCreateProgram;
extern PFNGLATTACHSHADERPROC                 glAttachShader;
extern PFNGLLINKPROGRAMPROC                  glLinkProgram;
extern PFNGLGETPROGRAMIVPROC                 glGetProgramiv;
extern PFNGLDELETEPROGRAMPROC                glDeleteProgram;
extern PFNGLGENBUFFERSPROC                   glGenBuffers;
extern PFNGLBINDBUFFERPROC                   glBindBuffer;
extern PFNGLBUFFERDATAPROC                   glBufferData;
extern PFNGLENABLEVERTEXATTRIBARRAYPROC      glEnableVertexAttribArray;
extern PFNGLDISABLEVERTEXATTRIBARRAYPROC     glDisableVertexAttribArray;
extern PFNGLVERTEXATTRIBPOINTERPROC          glVertexAttribPointer;
extern PFNGLDRAWARRAYSPROC                   glDrawArrays;
extern PFNGLUSEPROGRAMPROC                   glUseProgram;
extern PFNGLGENVERTEXARRAYPROC               glGenVertexArrays;
extern PFNGLBINDVERTEXARRAYPROC              glBindVertexArray;
extern PFNGLUNIFORM1FPROC                    glUniform1f;
extern PFNGLUNIFORM2FPROC                    glUniform2f;
extern PFNGLUNIFORM3FPROC                    glUniform3f;
extern PFNGLUNIFORM4FPROC                    glUniform4f;
extern PFNGLUNIFORMMATRIX4FVPROC             glUniformMatrix4fv;
extern PFNGLGETUNIFORMLOCATIONPROC           glGetUniformLocation;

extern PFNGLGENFRAMEBUFFERSPROC              glGenFramebuffers;
extern PFNGLBINDFRAMEBUFFERPROC              glBindFramebuffer;
extern PFNGLCHECKNAMEDFRAMEBUFFERSTATUSPROC  glCheckNamedFramebufferStatus;
extern PFNGLDELETEFRAMEBUFFERSPROC           glDeleteFramebuffers;
extern PFNGLGENTEXTURESPROC                  glGenTextures;
extern PFNGLBINDTEXTUREPROC                  glBindTexture;
extern PFNGLFRAMEBUFFERTEXTURE2DPROC         glFramebufferTexture2D;

Rc_t init_opengl( void );

} // end namespace OpenGL

Rc_t init_render_context( struct platform_window_t* window );
void buffer_swap( struct platform_window_t* window );

} // end namespace Engine

#endif //__OPENGL_WIN32_H__

