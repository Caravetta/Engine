#ifndef __ARCHETYPE_MANAGER_H__
#define __ARCHETYPE_MANAGER_H__

#include "core_common.h"
#include "archetype.h"
#include "entity.h"
#include "component_manager.h"

namespace Engine {
namespace Archetype_Manager {

UhRC_t init( void );

/**
    Register an archetype to a string name that will allow them to get this archetype back at a later date.

    @param archetype        holds the archetype data.
    @param archetype_name   name to map to the passed archetype.

    @return UhRC_t returns a return code.
*/
UhRC_t register_archetype( Archetype archetype, std::string archetype_name );

/**
    Register and entity with the archetype system.

    @param entity           the entity handle
    @param archetype_name   archetype to register the entity with

    @return UhRC_t returns a return code.
*/
UhRC_t register_entity( Entity entity, internal_entity_id* intern_entity_id, std::string archetype_name );

uint8_t* get_component_data_generic( internal_entity_id intern_entity_id, uint32_t component_id );
UhRC_t remove_entity( Entity entity );

template<typename T>
T* get_component_data( internal_entity_id id )
{
    return (T*)get_component_data_generic(id, Component_Manager::id<T>());
}

} //end namespace Archetype_Manager
} //end namespace Engine

#endif // __ARCHETYPE_MANAGER_H__
