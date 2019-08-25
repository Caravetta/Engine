#include "shader_gl.h"

#ifdef WINDOWS

#elif LINUX
#include "opengl_linux.h"
#else
     #error
#endif

namespace Engine {

Shader_GL::Shader_GL( std::vector<Shader_GL_File> files )
{
     for ( size_t ii = 0; ii < files.size(); ii++ ) {

     }
}

unsigned int Shader_GL::id( void )
{
     return __id;
}

} // end namespace Engine

