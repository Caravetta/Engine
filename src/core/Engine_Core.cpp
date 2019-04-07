#include "Engine_Core.h"

#include <iostream>
#include <typeinfo>
#include <typeindex>

namespace Engine {

/****************************************/
/*                                      */
/*         Basic Engine Calls           */
/*                                      */
/****************************************/

Rc_t init( const engine_config_t* config )
{
    UNUSED_ARG( config );
    Rc_t rc = SUCCESS;

    rc = init_ecs();
    if ( rc != SUCCESS ) {
        LOG_ERROR("Failed to initialize ECS");
        return rc;
    }

    return rc;
}

void shutdown( void )
{

}

} // end namespace Engine

