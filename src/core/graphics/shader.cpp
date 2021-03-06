#include <unordered_map>
#include "shader.h"
#include "platform_graphics.h"

namespace Engine {

Shader::Shader( const std::vector<Shader_File>& files )
{
     __id = create_program_file((uint8_t*)&files);
}

Shader::Shader( const std::vector<Shader_String>& strings )
{
     __id = create_program_string((uint8_t*)&strings);
}

int32_t Shader::id( void )
{
     return __id;
}

int32_t Shader::attribute_id( const std::string& name )
{
     return fetch_attrib_id(__id, (uint8_t*)&name);
}

int32_t Shader::uniform_id( const std::string& name )
{
     return fetch_uniform_id(__id, (uint8_t*)&name);
}

void Shader::set_uniform_int1( int32_t location, int value )
{
     upload_uniform_int1(location, value);
}

void Shader::set_uniform_float1( int32_t location, float value )
{
     upload_uniform_float1(location, value);
}

void Shader::set_uniform_float2( int32_t location, float value_1, float value_2 )
{
     upload_uniform_float2(location, value_1, value_2);
}

void Shader::set_uniform_float3( int32_t location, float value_1, float value_2, float value_3 )
{
     upload_uniform_float3(location, value_1, value_2, value_3);
}

void Shader::set_uniform_float4( int32_t location, float value_1, float value_2, float value_3, float value_4 )
{
     upload_uniform_float4(location, value_1, value_2, value_3, value_4);
}

void Shader::set_uniform_mat4( int32_t location, Matrix4f* matrix )
{
     upload_uniform_mat4(location, (uint8_t*)matrix);
}

struct Shader_Manager {
     std::unordered_map<int32_t, Shader*> shader_map;
};

Shader_Manager* shader_manager = NULL;

Rc_t init_shader_manager( void )
{
     Rc_t rc = SUCCESS;

     if ( shader_manager == NULL ) {
          shader_manager = new (std::nothrow) Shader_Manager;
          if ( shader_manager == NULL ) {
               rc = MEMORY_ALLOC_FAILED;
          }
     }

     return rc;
}

void add_shader( int32_t id, Shader& shader )
{
     shader_manager->shader_map.insert({id, &shader});
}

Shader& get_shader( int32_t id )
{
     Shader* shader = NULL;

     std::unordered_map<int32_t, Shader*>::const_iterator iter = shader_manager->shader_map.find(id);
     if ( iter != shader_manager->shader_map.end() ) {
          shader = iter->second;
     }

     return *shader;
}

} // end namespace Engine

