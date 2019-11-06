#include "entity.h"
#include "handle.h"

namespace Engine {

#define ENTITY_HANDLE_BLOCK_SIZE 100

struct Entity_System {
     Handle_Manager handle_manager;
};

Entity_System* entity_system = NULL;

Rc_t init_entity_system( void )
{
     Rc_t rc = SUCCESS;

     if ( entity_system == NULL ) {
          entity_system = new (std::nothrow) Entity_System;
          if ( entity_system != NULL ) {
               entity_system->handle_manager.set_block_size(ENTITY_HANDLE_BLOCK_SIZE);
          } else {
               rc = MEMORY_ALLOC_FAILED;
          }
     }

     return rc;
}

Entity create_entity( void )
{
     Handle handle = entity_system->handle_manager.get_handle();
     size_t n_ent_handles = entity_system->handle_manager.num_handles();

     if ( n_ent_handles > map_info_size() ) {
          resize_map_info(n_ent_handles);
     }

     add_handle( handle );

     return (Entity)handle;
}

Entity create_entity( std::vector<Component_ID> components )
{
     Handle handle = entity_system->handle_manager.get_handle();
     size_t n_ent_handles = entity_system->handle_manager.num_handles();

     if ( n_ent_handles > map_info_size() ) {
          resize_map_info(n_ent_handles);
     }

     add_handle(handle, components);

     return (Entity)handle;
}

void delete_entity( Entity entity )
{
     entity_system->handle_manager.free_handle((Handle)entity);
     size_t n_ent_handles = entity_system->handle_manager.num_handles();

     if ( n_ent_handles < map_info_size() ) {
          resize_map_info(n_ent_handles);
     }

     remove_handle(entity);
}

Rc_t add_component( Entity entity, Component_ID id )
{
     return handle_add_component(entity, id);
}

Rc_t add_components( Entity entity, std::vector<Component_ID> components )
{
     return handle_add_components(entity, components);
}

Rc_t remove_component( Entity entity, Component_ID id )
{
     return handle_remove_component(entity, id);
}

Rc_t remove_components( Entity entity, std::vector<Component_ID> components )
{
     return handle_remove_components(entity, components);
}

std::vector<Component_ID> entity_components( Entity entity )
{
     return get_components(entity);
}

} // end namespace Engine

