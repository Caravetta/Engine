#include "ecs.h"
#include "component_data.h"

namespace Engine {

Rc_t init_ecs( void )
{
     Rc_t rc = init_entity_system();
     if ( rc != SUCCESS ) {
          LOG_ERROR("Failed to initiate entity system");
     }

     rc = init_component_system();
     if ( rc != SUCCESS ) {
          LOG_ERROR("Failed to initiate component system");
     }

     rc = init_system_systems();
     if ( rc != SUCCESS ) {
          LOG_ERROR("Failed to initiate system system");
     }

     rc = init_component_data_system();
     if ( rc != SUCCESS ) {
          LOG_ERROR("Failed to initiate component data system");
     }

     return rc;
}

void ecs_debug_print( void )
{
     comp_data_system_debug_print();
}

} // end namespace Engine

