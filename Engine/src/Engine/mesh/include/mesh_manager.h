#ifndef __MESH_MANAGER_H__
#define __MESH_MANAGER_H__

#include "Engine.h"
#include "vao.h"

namespace Engine {
namespace Mesh_Manager {

Rc_t init( void );
vao_t* get_mesh_vao( Mesh_Handle handle );
uint32_t get_indices_count( Mesh_Handle handle );

} // end namespace Mesh_Manager
} // end namespace Engine

#endif //__MESH_MANAGER_H__
