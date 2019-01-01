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
component_create_function get_component_create( uint32_t component_id );
component_copy_function get_component_copy( uint32_t component_id );

} // end namespace Component_Manager
} // end namespace Engine

#endif //__COMPONENT_MANAGER_H__
