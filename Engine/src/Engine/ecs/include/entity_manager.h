#ifndef __ENTITY_MANAGER_H__
#define __ENTITY_MANAGER_H__

#include <vector>
#include <utility>
#include <type_traits>

#include "core_common.h"
#include "entity.h"
#include "component_manager.h"
#include "component.h"
#include "archetype_manager.h"

namespace Engine {
namespace Entity_Manager {

Rc_t init( void );
internal_entity_id get_internal_id( Entity entity );

} // end namespace Entity_Manager
} // end namespace Engine

#endif //__ENTITY_MANAGER_H__
