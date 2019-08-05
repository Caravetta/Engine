#ifndef __ECS_H__
#define __ECS_H__

#include <string>
#include "core_common.h"
#include "entity.h"
#include "component.h"
#include "archetype.h"
#include "entity_group.h"
#include "component_data_array.h"

namespace Engine {

Rc_t init_ecs( void );

Rc_t register_archetype( std::string archetype_name, Archetype& archetype );

Entity create_entity( std::string archetype_name );
Rc_t remove_entity( Entity entity );
uint8_t* component_data( Component_ID id, Entity entity );
template<typename T> T* component_data( Entity entity );


template<typename T>
T* component_data( Entity entity )
{
     return (T*)component_data(0, entity);
}

} // end namespace Engine

#endif //__ECS_H__
