#include "engine_core.h"
#include "page_allocator.h"
#include "platform_graphics.h"

namespace Engine {

Engine_Core* Engine_Core::__instance = NULL;

Engine_Core::Engine_Core( void )
{
     // Do nothing
}

Rc_t Engine_Core::init( void )
{
     load_graphics_api(OPENGL_GRAPHICS_API);

     Rc_t rc = init_page_allocator(16000, 50);
     if ( rc != SUCCESS ) {
          LOG_ERROR("Failed to setup Page Allocator rc=%d", rc);
     }

     rc = Reflection::init_reflection_system();
     if ( rc != SUCCESS ) {
          LOG_ERROR("Failed to setup Reflection system rc=%d", rc);
     }

     rc = init_key_input_system();
     if ( rc != SUCCESS ) {
          LOG_ERROR("Failed to setup input system rc=%d", rc);
     }

     rc = init_mouse_system();
     if ( rc != SUCCESS ) {
          LOG_ERROR("Failed to setup mouse system rc=%d", rc);
     }

     rc = init_ecs();
     if ( rc != SUCCESS ) {
          LOG_ERROR("Failed to setup ECS system rc=%d", rc);
     }

     rc = init_mesh_asset_manager();
     if ( rc != SUCCESS ) {
          LOG_ERROR("Failed to setup Mesh Asset system rc=%d", rc);
     }

     rc = init_shader_manager();
     if ( rc != SUCCESS ) {
          LOG_ERROR("Failed to setup Shader Asset system rc=%d", rc);
     }

     return rc;
}

Engine_Core* Engine_Core::instance( void )
{
     if ( __instance == NULL ) {
          __instance = new (std::nothrow) Engine_Core;
     }

     return __instance;
}

Entity Engine_Core::create_entity( void )
{
     return ::Engine::create_entity();
}

Entity Engine_Core::create_entity( std::vector<Component_ID> components )
{
     return ::Engine::create_entity(components);
}

void Engine_Core::delete_entity( Entity entity )
{
     ::Engine::delete_entity(entity);
}

Rc_t Engine_Core::add_component( Entity entity, Component_ID id )
{
     return ::Engine::add_component(entity, id);
}

Rc_t Engine_Core::add_components( Entity entity, std::vector<Component_ID> components )
{
     return ::Engine::add_components(entity, components);
}

Rc_t Engine_Core::remove_component( Entity entity, Component_ID id )
{
     return ::Engine::remove_component(entity, id);
}

Rc_t Engine_Core::remove_components( Entity entity, std::vector<Component_ID> components )
{
     return ::Engine::remove_components(entity, components);
}

extern "C" Engine_Core* get_engine_core( void )
{
     return Engine_Core::instance();
}

} // end namespace Engine

