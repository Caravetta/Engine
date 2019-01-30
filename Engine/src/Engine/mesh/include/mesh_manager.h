#ifndef __MESH_MANAGER_H__
#define __MESH_MANAGER_H__

#include "Engine.h"
#include "vao.h"

namespace Engine {
namespace Mesh_Manager {

Rc_t init( void );
vao_t* get_mesh_vao( Mesh_Handle handle );
uint32_t get_indices_count( Mesh_Handle handle );
Mesh_Handle load_to_graphics_api( Mesh* mesh, mesh_usage_t usage_type );
Rc_t update_mesh( Mesh_Handle handle, Mesh* mesh );
Rc_t deload_from_graphics_api( Mesh_Handle handle );

} // end namespace Mesh_Manager
} // end namespace Engine

#endif //__MESH_MANAGER_H__
