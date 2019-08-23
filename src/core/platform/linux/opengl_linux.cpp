#include <GL/glx.h>
#include "opengl_linux.h"

namespace Engine {
namespace OpenGL {

Rc_t init_opengl( void )
{
     glGenVertexArrays = (glGenVertexArraysProc)glXGetProcAddress((const GLubyte*)"glGenVertexArrays");
     if ( glGenVertexArrays == NULL ) {
          LOG_ERROR("%s: Failed to load glGenVertexArrays", __FUNCTION__);
          return ENGINE_ERROR;
     }

     return SUCCESS;
}

} // end namespace OpenGL
} // end namespace Engine

