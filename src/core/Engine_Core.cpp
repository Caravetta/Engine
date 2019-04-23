#include "Engine_Core.h"

#include <iostream>
#include <typeinfo>
#include <typeindex>

#include "window.h"
#include "page_allocator.h"

namespace Engine {

#define DEFAULT_PAGE_SIZE 16000
#define DEFAULT_POOL_SIZE 100

/****************************************/
/*                                      */
/*         Basic Engine Calls           */
/*                                      */
/****************************************/

Rc_t init( const Engine_Config config )
{
     Rc_t rc = SUCCESS;

     rc = init_page_allocator(DEFAULT_PAGE_SIZE, DEFAULT_POOL_SIZE);
     if ( rc != SUCCESS ) {
          LOG_ERROR("Failed to initialize Page Allocator rc=%d", rc);
          return rc;
     }

     rc = init_ecs();
     if ( rc != SUCCESS ) {
          LOG_ERROR("Failed to initialize ECS rc=%d", rc);
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

