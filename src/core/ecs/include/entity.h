#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <vector>
#include "core_common.h"
#include "component.h"

namespace Engine {

#define INVALID_ENTITY 0

typedef uint64_t Entity;

Rc_t init_entity_system( void );

Entity create_entity( void );
Entity create_entity( std::vector<Component_ID> components );

//Entity create_entity( Prefab prefab );
void delete_entity( Entity entity );

Rc_t add_component( Entity entity, Component_ID id );
Rc_t add_components( Entity entity, std::vector<Component_ID> components );

Rc_t remove_component( Entity entity, Component_ID id );
Rc_t remove_components( Entity entity, std::vector<Component_ID> components );

std::vector<Component_ID> entity_components( Entity entity );

template<class T> T* get_component( Entity entity );

} // end namespace Engine

#include "entity.inl"

#endif //__ENTITY_H__
