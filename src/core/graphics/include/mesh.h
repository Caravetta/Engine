#ifndef __MESH_H__
#define __MESH_H__

#include <vector>
#include <string>
#include "core_common.h"
#include "reflection.h"
#include "component.h"

namespace Engine {

#define POSITION_ID 0
#define INVALID_MESH_HANDLE 0

typedef uint64_t Mesh_Handle;

enum Mesh_Type {
     STATIC_MESH,
     DYNAMIC_MESH,
};

struct Mesh_Data {
     std::vector<unsigned int>     indices;
     std::vector<float>            positions;
     std::vector<float>            normals;
     std::vector<float>            text_cords;
};

struct Mesh {
     Mesh_Data*     data;
     Mesh_Handle    handle;
     size_t         indices_offset;
     size_t         indices_count;
};

struct Mesh_Render_Info {
     size_t    indices_offset;
     size_t    indices_count;
     uint32_t  vertex_array_id;
     uint32_t  indice_buffer_id;
};

/*
 *   Mesh Info Component
 */

struct Mesh_Info {
     COMPONENT_DECLARE( Mesh_Info );

     Mesh_Handle handle;
};

Rc_t init_mesh_asset_manager( void );
Rc_t load_mesh( Mesh_Type type, std::string file );
Rc_t load_mesh( Mesh_Type type, std::string mesh_name, Mesh_Data& mesh_data );
Mesh_Handle mesh_handle( std::string mesh_name );
Mesh_Render_Info mesh_render_info( Mesh_Handle handle );

} // end namespace Engine

#endif //__MESH_H__
