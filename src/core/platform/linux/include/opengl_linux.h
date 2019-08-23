#ifndef __OPENGL_LINUX_H__
#define __OPENGL_LINUX_H__

#include <GL/gl.h>
#include "core_common.h"

namespace Engine {
namespace OpenGL {

typedef void (*glGenVertexArraysProc) (GLsizei , GLuint*);

static glGenVertexArraysProc glGenVertexArrays = NULL;

Rc_t init_opengl( void );

} // end namespace OpenGL
} // end namespace Engine

#endif //__OPENGL_LINUX_H__
