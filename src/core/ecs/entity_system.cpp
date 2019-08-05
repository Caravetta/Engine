#include "entity_system.h"
#include "archetype.h"
#include "archetype_system.h"

namespace Engine {

#define ENTITY_HANDLE_BLOCK_SIZE 100

typedef Handle Entity_Handle;

struct Entity_Info {
     Archetype_Node_Info data_info;
};

struct Entity_System {
     Handle_Manager handle_manager;
     std::vector<Entity_Info> entity_info_vec;
};

Entity_System* entity_system = NULL;

Rc_t init_entity_system( void )
{
     Rc_t rc = SUCCESS;

     if ( entity_system == NULL ) {
          entity_system = new (std::nothrow) Entity_System;
          if ( entity_system == NULL ) {
               rc = MEMORY_ALLOC_FAILED;
          } else {
               entity_system->handle_manager.set_block_size(ENTITY_HANDLE_BLOCK_SIZE);
          }
     }

     return rc;
}

Entity get_entity( std::string archetype_name )
{

     Entity_Handle handle = entity_system->handle_manager.get_handle();

     size_t num_ent_handles = entity_system->handle_manager.num_handles();

     if ( num_ent_handles > entity_system->entity_info_vec.size() ) {
          entity_system->entity_info_vec.resize(num_ent_handles);
     }

     Entity_Info& ent_info = entity_system->entity_info_vec[handle_index(handle)];

     Rc_t rc = init_data_node(archetype_name, ent_info.data_info);
     if ( rc != SUCCESS ) {
          /* failed to allocate data for entity */
          return_entity(handle);
          handle = INVALID_ENTITY;
     }

     return (Entity)handle;
}

Rc_t return_entity( Entity entity )
{
     entity_system->handle_manager.free_handle((Entity_Handle)entity);

     size_t num_ent_handles = entity_system->handle_manager.num_handles();

     if ( num_ent_handles < entity_system->entity_info_vec.size() ) {
          entity_system->entity_info_vec.resize(num_ent_handles);
     }

     return SUCCESS;
}

uint8_t* get_entity_data( Component_ID id, Entity entity )
{
     uint8_t* data = NULL;

     if ( entity_system->handle_manager.valid_handle((Entity_Handle)entity) ) {

          Entity_Info& ent_info = entity_system->entity_info_vec[handle_index((Entity_Handle)entity)];

          data = get_component_data(id, ent_info.data_info);
     }

     return data;
}

} // end namespace Engine

