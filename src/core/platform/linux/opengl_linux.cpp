#include <GL/glx.h>
#include "opengl_linux.h"

namespace Engine {
namespace OpenGL {

#if 0
#define OPENGL_LOAD( func_name, func_define ) \
     func_name = (func_define)wglGetProcAddress((const GLubyte*)#func_name); \
     if ( !func_name ) { LOG_ERROR("%s: Failed to load %s", __FUNCTION__, #func_name); return ENGINE_ERROR }
#endif

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

