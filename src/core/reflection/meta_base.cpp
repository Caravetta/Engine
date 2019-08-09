#include "meta_base.h"
#include "reflection_system.h"

namespace Engine {

const char* Meta_Base_ID_Strings[ Meta_Base_ID::ID_COUNT ] =
{
     "META_STRUCT",
};

Meta_Base::Meta_Base( void )
{
     __tag = NULL;
     __name = NULL;
     __size = 0;
}

Meta_Base::~Meta_Base( void )
{
     /* do nothing */
}

void Meta_Base::meta_register( void ) const
{
}

void Meta_Base::meta_unregister( void ) const
{

}


Meta_Base_Registrar* Meta_Base_Registrar::__s_head[Registrar_Base_Types::TYPE_COUNT] = { NULL };
Meta_Base_Registrar* Meta_Base_Registrar::__s_tail[Registrar_Base_Types::TYPE_COUNT] = { NULL };

Meta_Base_Registrar::Meta_Base_Registrar( const char* name )
{
     __name = name;
     __next = NULL;
}

void Meta_Base_Registrar::add_to_list( Registrar_Base_Types type, Meta_Base_Registrar* registrar )
{
     if ( __s_tail[type] != NULL ) {
          __s_tail[type]->__next = registrar;
          __s_tail[type] = registrar;
     } else {
          __s_tail[type] = registrar;
          __s_head[type] = registrar;
     }
}

void Meta_Base_Registrar::remove_from_list( Registrar_Base_Types type, Meta_Base_Registrar* registrar )
{

}

void Meta_Base_Registrar::register_type( Registrar_Base_Types type )
{
     for ( Meta_Base_Registrar* cur_reg = __s_head[type]; cur_reg; cur_reg = cur_reg->__next ) {
          cur_reg->meta_register();
     }
}

void Meta_Base_Registrar::unregister_type( Registrar_Base_Types type )
{

}

void Meta_Base_Registrar::add_type_to_registry( Meta_Base* type )
{
     Reflection::register_type(type);
}

void Meta_Base_Registrar::remove_type_from_registry( const Meta_Base* type )
{

}

} // end namespace Engine

