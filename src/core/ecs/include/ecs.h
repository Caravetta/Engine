#ifndef __ECS_H__
#define __ECS_H__

#include "component.h"
#include "entity.h"

namespace Engine {

Rc_t init_ecs( void );
void ecs_debug_print( void );

} // end namespace Engine

#endif //__ECS_H__
