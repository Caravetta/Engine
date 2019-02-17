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
internal_entity_id* get_internal_id_pointer( Entity entity );
void update();
Entity create_entity( const std::string archetype_name );
Rc_t delete_entity( const Entity entity );
bool is_valid_entity( const Entity entity );

} // end namespace Entity_Manager
} // end namespace Engine

#endif //__ENTITY_MANAGER_H__
