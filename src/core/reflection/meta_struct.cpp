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

Meta_Field* Meta_Struct::allocate_field( void )
{
     Meta_Field field;
     __fields.push_back(field);

     return &__fields.back();
}

void Meta_Struct::print_struct_info( void )
{
     for ( size_t ii = 0; ii <  __fields.size(); ii++ ) {
          LOG("Name: %s Name_Crc: %" PRIu32 " Size: %" PRIu32 " Offset: %" PRIu32 "",
              __fields[ii].__name,
              __fields[ii].__name_crc,
              __fields[ii].__size,
              __fields[ii].__offset);
     }
}

} // end namespace Engine

