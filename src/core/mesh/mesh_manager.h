#ifndef __MESH_MANAGER_H__
#define __MESH_MANAGER_H__

namespace core {
namespace Mesh_Manager {

typedef base_handle_t Mesh_Handle;

UhRC_t init( void );
UhRC_t add_mesh( Mesh* mesh );
Mesh* get_mesh( Mesh_Handle handle );


} // end namespace Mesh_Manager
} // end namespace core

#endif //__MESH_MANAGER_H__
