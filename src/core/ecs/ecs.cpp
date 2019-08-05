#include "ecs.h"
#include "entity_system.h"
#include "archetype_system.h"

namespace Engine {

Rc_t init_ecs( void )
{
     Rc_t rc = init_entity_system();
     if ( rc != SUCCESS ) {
          LOG_ERROR("Failed to initiate entity system");
     }

     rc = init_archetype_system();
     if ( rc != SUCCESS ) {
          LOG_ERROR("Failed to initiate archetype system");
     }

     return rc;
}

Rc_t register_archetype( std::string archetype_name, Archetype& archetype )
{
     return add_archetype(archetype, archetype_name);
}

Entity create_entity( std::string archetype_name )
{
     return get_entity(archetype_name);
}

Rc_t remove_entity( Entity entity )
{
     return return_entity(entity);
}

uint8_t* component_data( Component_ID id, Entity entity )
{
     return get_entity_data(id, entity);
}

} // end namespace Engine

