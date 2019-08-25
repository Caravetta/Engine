#ifndef __OPENGL_WIN32_H__
#define __OPENGL_WIN32_H__

#include <windows.h>
#include <gl/gl.h>
#include "core_common.h"

namespace Engine {
namespace OpenGL {

typedef HGLRC(WINAPI * PFNWGLCREATECONTEXTATTRIBSARBPROC) ( HDC hDC, HGLRC hShareContext, const int *attribList );
typedef BOOL(WINAPI * PFNWGLCHOOSEPIXELFORMATARBPROC) ( HDC hdc, const int *piAttribIList, const FLOAT *pfAttribFList,
                                                        UINT nMaxFormats, int *piFormats, UINT *nNumFormats );

extern PFNWGLCREATECONTEXTATTRIBSARBPROC     wglCreateContextAttribsARB;
extern PFNWGLCHOOSEPIXELFORMATARBPROC        wglChoosePixelFormatARB;

typedef void (*glGenVertexArraysProc) (GLsizei , GLuint*);

static glGenVertexArraysProc glGenVertexArrays = NULL;

Rc_t init_opengl( void );

} // end namespace OpenGL
} // end namespace Engine

#endif //__OPENGL_WIN32_H__
