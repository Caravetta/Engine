#ifndef __ENTITY_ARCHETYPE_MANAGER_H__
#define __ENTITY_ARCHETYPE_MANAGER_H__

#include "../core_common.h"
#include "entity_archetype.h"
#include "entity.h"

namespace core {
namespace Entity_Archetype_Manager {

CORE_API UhRC_t init( void );

/**
    Register an archetype to a string name that will allow them to get this archetype back at a later date.

    @param archetype        holds the archetype data.
    @param archetype_name   name to map to the passed archetype.

    @return UhRC_t returns a return code.
*/
CORE_API UhRC_t register_archetype( Entity_Archetype archetype, std::string archetype_name );

/**
    Register and entity with the archetype system.

    @param entity           the entity handle
    @param archetype_name   archetype to register the entity with

    @return UhRC_t returns a return code.
*/
CORE_API UhRC_t register_entity( Entity entity, std::string archetype_name );

CORE_API uint8_t* get_component_data_generic( Entity entity, uint32_t component_id );
CORE_API UhRC_t remove_entity( Entity entity );

template<typename T>
T* get_component_data( Entity entity )
{
    return (T*)get_component_data_generic(entity, Component_Manager::id<T>());
}

} //end namespace Entity_Archetype_Manager
} //end namespace core

#endif // __ENTITY_ARCHETYPE_MANAGER_H__
