
#include "crc32.h"

namespace Engine {

#define GET_FIELD_OFFSET( __struct, __field ) (uint32_t) (uintptr_t) &( ((__struct*)NULL)->*__field)

template<class T>
void Meta_Info::create( Meta_Info const*& meta_info, const char* name )
{
     Meta_Info* tmp_struct = Meta_Info::create();
     meta_info = tmp_struct;

     Meta_Info::create<T>(name, &T::populate_meta_info_func, tmp_struct);
}

template<class T>
void Meta_Info::create( const char* name, populate_meta_info_func func, Meta_Info* info )
{
     info->__size = sizeof(T);
     info->__name = name;
     info->__populate_func = func;
}

template<class T>
Meta_Info_Registrar<T>::Meta_Info_Registrar( void )
     : Meta_Info_Base_Registrar()
{
     Meta_Info_Base_Registrar::add_to_list(this);
}

template<class T>
Meta_Info_Registrar<T>::~Meta_Info_Registrar( void )
{
     // do nothing
}

template<class T>
void Meta_Info_Registrar<T>::meta_info_register( void )
{
     if ( T::__s_meta_info == NULL ) {
          const Meta_Info* tmp = T::create_meta_info();
          Meta_Info_Base_Registrar::add_meta_info(tmp);
     }
}

template<class Struct_T, class Field_T>
void Meta_Info::add_field( Field_T Struct_T::* field, const char* name, uint32_t flags )
{
     Meta_Field new_field;
     new_field.__name = name;
     new_field.__name_crc = crc32(name);
     new_field.__size = sizeof(Field_T);
     new_field.__offset = GET_FIELD_OFFSET(Struct_T, field);
     new_field.type = new_field.get_field_type<Field_T>();

     __fields.push_back(new_field);
}

} // end namespace Engine

