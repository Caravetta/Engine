#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <vector>
#include "core_common.h"
#include "component.h"

namespace Engine {

#define INVALID_ENTITY 0

typedef uint64_t Entity;

Rc_t init_entity_system( void );

extern "C" Entity create_entity( Component_ID* ids, size_t n_ids );

//Entity create_entity( Prefab prefab );
extern "C" void delete_entity( Entity entity );

extern "C" Rc_t add_components( Entity entity, Component_ID* ids, size_t n_ids );

extern "C" Rc_t remove_components( Entity entity, Component_ID* ids, size_t n_ids );

std::vector<Component_ID> entity_components( Entity entity ); //TODO(JOSH): need to figure out a replacement for this

template<class T> T* get_component( Entity entity );

} // end namespace Engine

#include "entity.inl"

#endif //__ENTITY_H__
