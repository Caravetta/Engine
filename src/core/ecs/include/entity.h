#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "core_common.h"
#include "handle.h"

namespace Engine {

COMPONENT()
struct Entity {
     Handle handle;
};

Rc_t init_entity_system( void );
Entity get_entity_id( void );
Rc_t free_entity_id( const Entity entity );

} // end namespace Engine

#endif // __ENTITY_H__

