#ifndef __MESH_H__
#define __MESH_H__

#include <vector>
#include <string>
#include "core_common.h"
#include "component.h"
#include "reflection.h"

namespace Engine {

#define POSITION_ID 0
#define NORMAL_ID 1
#define INVALID_MESH_HANDLE 0

typedef uint64_t Mesh_Handle;

enum Mesh_Type {
     STATIC_MESH,
     DYNAMIC_MESH,
};

ENGINE_STRUCT()
struct Mesh_Data {
     ENGINE_CLASS_BODY()

     ENGINE_PROPERTY()
     std::vector<unsigned int>     indices;

     ENGINE_PROPERTY()
     std::vector<float>            positions;

     ENGINE_PROPERTY()
     std::vector<float>            normals;

     ENGINE_PROPERTY()
     std::vector<float>            text_cords;
};

ENGINE_STRUCT()
struct Mesh {
     ENGINE_CLASS_BODY()

     ENGINE_PROPERTY()
     std::string    mesh_name;
     Mesh_Data*     data;
     Mesh_Handle    handle;
     size_t         indices_offset;
     size_t         indices_count;
     uint32_t       vertex_array_id;
     uint32_t       indice_buffer_id;
     uint32_t       vertex_buffer_id;
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

ENGINE_STRUCT()
struct Mesh_Info {
     COMPONENT_DECLARE( Mesh_Info );
     META_INFO_DECLARE( Mesh_Info );

     ENGINE_COMPONENT()

     static void populate_meta_info_func( Engine::Meta_Info& meta_info );

     ENGINE_PROPERTY()
     Engine::Mesh_Handle handle;
};

Rc_t init_mesh_asset_manager( void );
//Rc_t load_mesh( Mesh_Type type, std::string file );
Rc_t load_mesh( Mesh_Type type, std::string mesh_name, Mesh_Data& mesh_data );
Mesh_Handle mesh_handle( std::string mesh_name );
Mesh_Render_Info mesh_render_info( Mesh_Handle handle );
Rc_t  bind_mesh( const Mesh_Handle& mesh_handle, size_t& ind );

} // end namespace Engine

#endif //__MESH_H__
