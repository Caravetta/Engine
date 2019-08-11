#include "component.h"

namespace Engine {

Rc_t init_component_system( void )
{
     Component_Base_Registrar::register_components();
     return SUCCESS;
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

