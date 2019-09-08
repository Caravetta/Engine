#ifndef __SHADER_COMMON_H__
#define __SHADER_COMMON_H__

#include <string>

namespace Engine {

enum Shader_Type {
     VERTEX_SHADER       = 0x8B31,
     FRAGMENT_SHADER     = 0x8B30,
     GEOMETRY_SHADER     = 0x8DD9,
};

struct Shader_File {
     Shader_Type    type;
     std::string    file;
};

struct Shader_String {
     Shader_Type    type;
     char*          source;
     size_t         length;
};

} // end namespace Engine

#endif //__SHADER_COMMON_H__
