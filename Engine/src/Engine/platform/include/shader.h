#ifndef __SHADER_H__
#define __SHADER_H__

#include <string.h>
#include "Engine.h"
#include "core_common.h"

namespace Engine {

typedef enum {
    VERTEX_SHADER   = 0x8B31,
    FRAGMENT_SHADER = 0x8B30,
    GEOMETRY_SHADER = 0x8DD9,
} shader_type_t;

typedef struct {
    std::string     file_name;
    shader_type_t   type;
} shader_file_t;

typedef struct {
    uint32_t vert_id;
    uint32_t frag_id;
    uint32_t geom_id;
    uint32_t prog_id;
} shader_t;

uint32_t create_shader(shader_file_t shader_files[], uint8_t size);
void load_shader_file( std::string file_name, shader_type_t type, unsigned int* id );
//void create_shader_program( unsigned int vertex_id, unsigned int fragment_id, unsigned int* program_id );

class Shader {
public:
    unsigned int vert_id;
    unsigned int frag_id;
    unsigned int geom_id;
    unsigned int prog_id;

    Shader( std::string vert_file, std::string frag_file );
    Shader( std::string vert_file, std::string frag_file, std::string geom_file );
    Rc_t set_value( std::string variable_name, float value);
    //Rc_t set_value( std::string variable_name, Vector2f value);
    Rc_t set_value( std::string variable_name, Vector3f value);
    Rc_t set_value( std::string variable_name, Matrix4f value);
private:
    void load_shader( std::string file_name, shader_type_t type );
    void create_program( bool has_geom );
};

} //end namespace Engine

#endif //__SHADER_H__
