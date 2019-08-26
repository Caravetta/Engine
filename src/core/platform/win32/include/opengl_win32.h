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
typedef void (APIENTRY * PFNGLVERTEXATTRIBPOINTERPROC) ( GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *pointer );
typedef void (APIENTRY * PFNGLDRAWARRAYSPROC) ( GLenum mode, GLint first, GLsizei count );
typedef void (APIENTRY * PFNGLUSEPROGRAMPROC) ( GLuint program );

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

Rc_t init_opengl( void );

} // end namespace OpenGL
} // end namespace Engine

#endif //__OPENGL_WIN32_H__
