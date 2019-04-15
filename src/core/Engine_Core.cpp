#include "Engine_Core.h"

#include <iostream>
#include <typeinfo>
#include <typeindex>

#include "window.h"

namespace Engine {

/****************************************/
/*                                      */
/*         Basic Engine Calls           */
/*                                      */
/****************************************/

Rc_t init( const Engine_Config config )
{
     Rc_t rc = SUCCESS;

     rc = init_ecs();
     if ( rc != SUCCESS ) {
          LOG_ERROR("Failed to initialize ECS");
          return rc;
     }

     rc = Window::create(config.window_width, config.window_height, config.window_title);
     if ( rc != SUCCESS ) {
          LOG_ERROR("Failed to create window rc=%d", rc);
          return rc;
     }

     return rc;
}

void run( void )
{
     while ( !Window::is_closed() ) {
          Window::update();
          Window::swap_buffers();
     }
}

void shutdown( void )
{

}

} // end namespace Engine

