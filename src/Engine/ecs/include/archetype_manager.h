#ifndef __ARCHETYPE_MANAGER_H__
#define __ARCHETYPE_MANAGER_H__

#include "core_common.h"
#include "entity.h"
#include "component_manager.h"

namespace Engine {
namespace Archetype_Manager {

Rc_t init( void );

/**
    Register and entity with the archetype system.

    @param entity           the entity handle
    @param archetype_name   archetype to register the entity with

    @return UhRC_t returns a return code.
*/
Rc_t register_entity( const Entity entity, internal_entity_id* intern_entity_id, const std::string archetype_name );
void update_entity_counts( void );
u8* get_component_data_generic( const internal_entity_id intern_entity_id, const u32 component_id );
Rc_t remove_entity( internal_entity_id intern_entity_id );
Rc_t register_archetype( Archetype archetype, std::string archetype_name );

template<typename T>
T* get_component_data( internal_entity_id id )
{
    return (T*)get_component_data_generic(id, component_id<T>());
}

} //end namespace Archetype_Manager
} //end namespace Engine

#endif // __ARCHETYPE_MANAGER_H__
