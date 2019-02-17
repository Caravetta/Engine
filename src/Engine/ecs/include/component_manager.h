#ifndef __COMPONENT_MANAGER_H__
#define __COMPONENT_MANAGER_H__

#include <vector>
#include <utility>
#include <type_traits>
#include <bitset>
#include <limits>
#include "core_common.h"
#include "component.h"
#include "Engine.h"

namespace Engine {
namespace Component_Manager {

Rc_t init( void );
component_create_function get_component_create( const u32 component_id );
component_copy_function get_component_copy( const u32 component_id );
u32 get_max_components( void );
u64 get_component_size( const u32 component_id );
void register_component_info( const u32 component_id, const component_info comp_info );
u8* get_component_data( const Entity entity, const u32 component_id );

} // end namespace Component_Manager
} // end namespace Engine

#endif //__COMPONENT_MANAGER_H__
