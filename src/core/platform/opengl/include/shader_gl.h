#ifndef __SHADER_GL_H__
#define __SHADER_GL_H__

#include <vector>
#include <string>
#include "core_common.h"
#include "matrix4f.h"

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

struct Shader_GL_String {
     Shader_GL_Type type;
     char*          source;
     size_t         length;
};

class Shader_GL {
private:
     int32_t __id;

public:
     Shader_GL( std::vector<Shader_GL_File> files );
     Shader_GL( std::vector<Shader_GL_String> strings );
     int32_t id( void );
     int32_t uniform_id( std::string name );
     void set_uniform_float1( int32_t location, float value );
     void set_uniform_float2( int32_t location, float value_1, float value_2 );
     void set_uniform_float3( int32_t location, float value_1, float value_2, float float_3 );
     void set_uniform_float4( int32_t location, float value_1, float value_2, float float_3, float float_4 );
     void set_uniform_mat4( int32_t location, Matrix4f* matrix );
};

};

#endif //__SHADER_GL_H__
