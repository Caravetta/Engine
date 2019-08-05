#ifndef __ENTITY_SYSTEM_H__
#define __ENTITY_SYSTEM_H__

#include <string>
#include "core_common.h"
#include "handle.h"
#include "entity.h"
#include "component.h"

namespace Engine {

Rc_t init_entity_system( void );
Entity get_entity( std::string archetype_name );
Rc_t return_entity( Entity entity );
uint8_t* get_entity_data( Component_ID id, Entity entity );

}; // end namespace Engine

#endif //__ENTITY_SYSTEM_H__

