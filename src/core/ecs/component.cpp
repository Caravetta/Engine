#include <vector>
#include "component.h"

namespace Engine {

struct Component_Manager {
     std::vector<Component_Info> comp_info_vec;
};

Component_Manager* component_manager = NULL;

Rc_t init_component_system( void )
{
     Rc_t rc = SUCCESS;

     if ( component_manager == NULL ) {
          component_manager = new (std::nothrow) Component_Manager;
          if ( component_manager == NULL ) {
               rc = MEMORY_ALLOC_FAILED;
               LOG_ERROR("Failed to allocate memory for component system");
          }
     } else {
          rc = ENGINE_ERROR;
          LOG_ERROR("Component system all ready initialized");
     }

     return rc;
}

Rc_t register_component_info( const Component_ID id, const Component_Info info )
{
     Rc_t rc = SUCCESS;

     if ( component_manager != NULL ) {
          std::vector<Component_Info>* comp_info_vec = &component_manager->comp_info_vec;

          if ( id >= comp_info_vec->size() ) {
               comp_info_vec->resize( id + 1 );
          }

          comp_info_vec->at(id) = info;
     } else {
          rc = ENGINE_ERROR;
           LOG_ERROR("Component system not initialized");
     }

     return rc;
}

component_create_function get_component_create( const Component_ID id )
{
     component_create_function create_func = NULL;

     if ( component_manager != NULL ) {
          std::vector<Component_Info>* comp_info_vec = &component_manager->comp_info_vec;

          if ( id < comp_info_vec->size() ) {
               create_func = comp_info_vec->at(id).create_function;
          } else {
               LOG_ERROR("Index [%" PRIu32 "] out of bounds", id);
          }
     } else {
          LOG_ERROR("Component system not initialized");
     }

     return create_func;
}

component_copy_function get_component_copy( const Component_ID id )
{
     component_copy_function copy_func = NULL;

     if ( component_manager != NULL ) {
          std::vector<Component_Info>* comp_info_vec = &component_manager->comp_info_vec;

          if ( id < comp_info_vec->size() ) {
               copy_func = comp_info_vec->at(id).copy_function;
          } else {
               LOG_ERROR("Index [%" PRIu32 "] out of bounds", id);
          }
     } else {
          LOG_ERROR("Component system not initialized");
     }

     return copy_func;
}

uint64_t get_component_size( const Component_ID id )
{
     uint64_t comp_size = 0;

     if ( component_manager != NULL ) {
          std::vector<Component_Info>* comp_info_vec = &component_manager->comp_info_vec;

          if ( id < comp_info_vec->size() ) {
               comp_size = comp_info_vec->at(id).size;
          } else {
               LOG_ERROR("Index [%" PRIu32 "] out of bounds", id);
          }
     } else {
          LOG_ERROR("Component system not initialized");
     }

     return comp_size;
}

Component_Type get_component_type( const Component_ID id )
{
     Component_Type comp_type = UNDEFINED_COMPONENT_TYPE;

     if ( component_manager != NULL ) {
          std::vector<Component_Info>* comp_info_vec = &component_manager->comp_info_vec;

          if ( id < comp_info_vec->size() ) {
               comp_type = comp_info_vec->at(id).type;
          } else {
               LOG_ERROR("Index [%" PRIu32 "] out of bounds", id);
          }
     } else {
          LOG_ERROR("Component system not initialized");
     }

     return comp_type;
}

} // end namespace Engine

