#include "engine_core.h"
#include "page_allocator.h"

namespace Engine {

Rc_t engine_init( void )
{
     Rc_t rc = init_page_allocator( 16000, 50 );
     if ( rc != SUCCESS ) {
          LOG_ERROR("Failed to setup Page Allocator rc=%d", rc);
     }

     rc = Reflection::init_reflection_system();
     if ( rc != SUCCESS ) {
          LOG_ERROR("Failed to setup Reflection system rc=%d", rc);
     }

     rc = init_ecs();
     if ( rc != SUCCESS ) {
          LOG_ERROR("Failed to setup ECS system rc=%d", rc);
     }

     rc = OpenGL::init_opengl();
     if ( rc != SUCCESS ) {
          LOG_ERROR("Failed to setup OpenGL rc=%d", rc);
     }

     return rc;
}

} // end namespace Engine

