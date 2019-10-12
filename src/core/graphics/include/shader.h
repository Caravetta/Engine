#ifndef __SHADER_H__
#define __SHADER_H__

#include <vector>
#include <string>
#include "core_common.h"
#include "shader_common.h"
#include "matrix4f.h"

namespace Engine {

class Shader {
private:
     int32_t __id;

public:
     Shader( const std::vector<Shader_File>& files );
     Shader( const std::vector<Shader_String>& strings );
     int32_t id( void );
     int32_t uniform_id( const std::string& name );
     void set_uniform_int1( int32_t location, int value );
     void set_uniform_float1( int32_t location, float value );
     void set_uniform_float2( int32_t location, float value_1, float value_2 );
     void set_uniform_float3( int32_t location, float value_1, float value_2, float value_3 );
     void set_uniform_float4( int32_t location, float value_1, float value_2, float value_3, float value_4 );
     void set_uniform_mat4( int32_t location, Matrix4f* matrix );
};

} // end namespace Engine

#endif //__SHADER_H__
