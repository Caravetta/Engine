#ifndef __ECS_H__
#define __ECS_H__

#include "component.h"
#include "entity.h"
#include "entity_group.h"
#include "system.h"
#include "component_data_array.h"
#include "default_components.h"

namespace Engine {

Rc_t init_ecs( void );
void ecs_debug_print( void );

} // end namespace Engine

#endif //__ECS_H__
