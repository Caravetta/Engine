#ifndef __ENTITY_MANAGER_H__
#define __ENTITY_MANAGER_H__

#include <vector>
#include <utility>
#include <type_traits>

#include "../core_common.h"
#include "entity.h"
#include "../component_system/component_manager.h"
#include "../component_system/component.h"
#include "entity_archetype_manager.h"

namespace core {
namespace Entity_Manager {

CORE_API UhRC_t init( void );
CORE_API Entity create_entity( std::string archetype_name );
CORE_API UhRC_t delete_entity( Entity entity );
CORE_API bool is_valid_entity( Entity entity );
CORE_API internal_entity_id get_internal_id( Entity entity );

template<typename T>
UhRC_t add_component( Entity entity )
{
    //TODO(JOSH): need to implement.
    CHECK_INFO( 0, "entity_manager_add_component not implemented" );
    return SUCCESS;
}

template<typename T>
UhRC_t remove_component( Entity entity )
{
    //TODO(JOSH): need to implement.
    CHECK_INFO( 0, "entity_manager_remove_component not implemented" );
    return SUCCESS;
}

template<typename T>
T* get_component( Entity entity )
{
    return Entity_Archetype_Manager::get_component_data<T>(get_internal_id(entity));
}

template<typename T>
bool is_component_set( Entity entity )
{
    return false;
}

} // end namespace Entity_Manager
} // end namespace core

#endif //__ENTITY_MANAGER_H__
