#include "meta_struct.h"

namespace Engine {

Meta_Struct::Meta_Struct( void )
{
     __base_struct = NULL;
}

Meta_Struct::~Meta_Struct( void )
{

}

Meta_Struct* Meta_Struct::create( void )
{
     return new Meta_Struct();
}

void Meta_Struct::meta_register( void ) const
{
     Meta_Base::meta_register();
}

void Meta_Struct::meta_unregister( void ) const
{
     Meta_Base::meta_unregister();
}

void Meta_Struct::add_derived_struct( const Meta_Struct* derived ) const
{

}

} // end namespace Engine

