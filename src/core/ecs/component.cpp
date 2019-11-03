#include <vector>
#include "component.h"

namespace Engine {

struct Component_Info {
     size_t size;
     comp_mem_init_func mem_init;
     comp_mem_cpy_func mem_cpy;
};

struct Component_System {
     std::vector<Component_Info> comp_info;
};

Component_System* component_system = NULL;

Rc_t init_component_system( void )
{
     Rc_t rc = SUCCESS;

     if ( component_system == NULL ) {
          component_system = new (std::nothrow) Component_System;
          if ( component_system != NULL ) {
               component_system->comp_info.push_back(Component_Info());
               Component_Base_Registrar::register_components();
          } else {
               rc = MEMORY_ALLOC_FAILED;
          }
     }

     return rc;
}

void add_component_info( Component_ID id , size_t size, comp_mem_init_func mem_init, comp_mem_cpy_func mem_cpy )
{
     Component_Info info;
     info.size = size;
     info.mem_init = mem_init;
     info.mem_cpy = mem_cpy;
     component_system->comp_info.push_back(info);
}

comp_mem_init_func component_mem_init( Component_ID id )
{
     return component_system->comp_info[id].mem_init;
}

comp_mem_cpy_func component_mem_cpy( Component_ID id )
{
     return component_system->comp_info[id].mem_cpy;
}

size_t component_size( Component_ID id )
{
     return component_system->comp_info[id].size;
}

Component_Base_Registrar* Component_Base_Registrar::__s_head = NULL;
Component_Base_Registrar* Component_Base_Registrar::__s_tail = NULL;

Component_Base_Registrar::Component_Base_Registrar( void )
{
     __next = NULL;
}

Component_Base_Registrar::~Component_Base_Registrar( void )
{
     //do nothing
}

void Component_Base_Registrar::add_to_list( Component_Base_Registrar* registrar )
{
     if ( __s_tail != NULL ) {
          __s_tail->__next = registrar;
          __s_tail = registrar;
     } else {
          __s_tail = registrar;
          __s_head = registrar;
     }
}

void Component_Base_Registrar::register_components( void )
{
     Component_ID cur_id = 1;
     for ( Component_Base_Registrar* cur_reg = __s_head; cur_reg; cur_reg = cur_reg->__next ) {
          cur_reg->component_register(cur_id);
          cur_id += 1;
     }
}

} // end namespace Engine

