#if !defined(SHADER_H)

#include <string.h>
#include "../../core_common.h"

namespace core {

    typedef enum {
        VERTEX_SHADER   = 0x8B31,
        FRAGMENT_SHADER = 0x8B30,
        GEOMETRY_SHADER = 0x8DD9,
    } shader_type_t;

    CORE_API void load_shader_file( std::string file_name, shader_type_t type, unsigned int* id );
    CORE_API void create_shader_program( unsigned int vertex_id, unsigned int fragment_id, unsigned int* program_id );

    class CORE_API Shader {
    public:
        unsigned int vert_id;
        unsigned int frag_id;
        unsigned int geom_id;
        unsigned int prog_id;

        Shader( std::string vert_file, std::string frag_file );
        Shader( std::string vert_file, std::string frag_file, std::string geom_file );
    private:
        void load_shader( std::string file_name, shader_type_t type );
        void create_program( bool has_geom );
    };

} //end namespace core

#define SHADER_H
#endif
