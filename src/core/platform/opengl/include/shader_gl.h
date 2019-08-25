#ifndef __SHADER_GL_H__
#define __SHADER_GL_H__

#include <vector>
#include <string>
#include "core_common.h"

namespace Engine {

enum Shader_GL_Type {
     VERTEX_SHADER       = 0x8B31,
     FRAGMENT_SHADER     = 0x8B30,
     GEOMETRY_SHADER     = 0x8DD9,
};

struct Shader_GL_File {
     Shader_GL_Type type;
     std::string    file;
};

class Shader_GL {
private:
     unsigned int __id;

public:
     Shader_GL( std::vector<Shader_GL_File> files );
     unsigned int id( void );
};

};

#endif //__SHADER_GL_H__
