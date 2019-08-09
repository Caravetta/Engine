
#include "reflection_system.h"

namespace Engine {

template<class T>
void Meta_Struct::create( Meta_Struct const*& meta_struct, const char* name, const char* base_name )
{
     Meta_Struct* tmp_struct = Meta_Struct::create();
     meta_struct = tmp_struct;

     Meta_Struct::create<T>(name, base_name, &T::populate_meta_struct_func, tmp_struct);
}

template<class T>
void Meta_Struct::create( const char* name, const char* base_name, populate_meta_struct_func func, Meta_Struct* info )
{
     info->__size = sizeof(T);
     info->__name = name;

     bool base_populate = false;

     if ( base_name ) {
          info->__base_struct = Reflection::get_meta_struct(base_name);
          info->__base_struct->add_derived_struct(info);
     }

     const Meta_Struct* base_struct = info->__base_struct;
     while ( base_populate == false && base_struct ) {
          if ( base_struct ) {
               base_populate = base_struct->__populate_func && base_struct->__populate_func == func;
               base_struct = base_struct->__base_struct;
          } else {
               base_name = NULL;
          }
     }

     if ( base_populate == false ) {
          info->__populate_func = func;
     }

     if ( info->__populate_func ) {
          info->__populate_func( *info );
     }
}


template<class Class_T, class Base_T>
Meta_Struct_Registrar<Class_T, Base_T>::Meta_Struct_Registrar( const char* name )
     : Meta_Base_Registrar( name )
{
     Meta_Base_Registrar::add_to_list(Registrar_Base_Types::META_STRUCT_TYPE, this);
}

template<class Class_T, class Base_T>
Meta_Struct_Registrar<Class_T, Base_T>::~Meta_Struct_Registrar( void )
{
     meta_unregister();
     Meta_Base_Registrar::remove_from_list(Registrar_Base_Types::META_STRUCT_TYPE, this);
}

template<class Class_T, class Base_T>
void Meta_Struct_Registrar<Class_T, Base_T>::meta_register( void )
{
     if ( Class_T::__s_meta_struct == NULL ) {
          Base_T::__s_meta_struct.meta_register();
          Meta_Base_Registrar::add_type_to_registry(Class_T::create_meta_struct());
     }
}

template<class Class_T, class Base_T>
void Meta_Struct_Registrar<Class_T, Base_T>::meta_unregister( void )
{
     if ( Class_T::__s_meta_struct != NULL ) {
          Meta_Base_Registrar::remove_type_from_registry(Class_T::__s_meta_struct);
          Class_T::__s_meta_struct = NULL;
     }
}


template<class Class_T>
Meta_Struct_Registrar<Class_T, void>::Meta_Struct_Registrar( const char* name )
     : Meta_Base_Registrar( name )
{
     Meta_Base_Registrar::add_to_list(Registrar_Base_Types::META_STRUCT_TYPE, this);
}

template<class Class_T>
Meta_Struct_Registrar<Class_T, void>::~Meta_Struct_Registrar( void )
{
     meta_unregister();
     Meta_Base_Registrar::remove_from_list(Registrar_Base_Types::META_STRUCT_TYPE, this);
}

template<class Class_T>
void Meta_Struct_Registrar<Class_T, void>::meta_register( void )
{
     if ( Class_T::__s_meta_struct == NULL ) {
          Meta_Base_Registrar::add_type_to_registry(Class_T::create_meta_struct());
     }
}

template<class Class_T>
void Meta_Struct_Registrar<Class_T, void>::meta_unregister( void )
{
     if ( Class_T::__s_meta_struct != NULL ) {
          Meta_Base_Registrar::remove_type_from_registry(Class_T::__s_meta_struct);
          Class_T::__s_meta_struct = NULL;
     }
}

} // end namespace Engine

