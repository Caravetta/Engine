#ifndef __ENGINE_CORE_H__
#define __ENGINE_CORE_H__

#include "core_common.h"
#include "ecs.h"
#include "engine_math.h"
#include "reflection.h"
#include "utils.h"
#include "input.h"
#include "graphics.h"

namespace Engine {

class Engine_Core {
public:
     static Engine_Core* instance( void );

     Rc_t init( void );

     Entity create_entity( void );
     Entity create_entity( std::vector<Component_ID> components );
     void delete_entity( Entity entity );
     Rc_t add_component( Entity entity, Component_ID id );
     Rc_t add_components( Entity entity, std::vector<Component_ID> components );
     Rc_t remove_component( Entity entity, Component_ID id );
     Rc_t remove_components( Entity entity, std::vector<Component_ID> components );

private:
     Engine_Core( void );
     static Engine_Core* __instance;
};

extern "C" ENGINE_API Engine_Core* get_engine_core( void );

} // end namespace Engine

#endif //__ENGINE_CORE_H__
