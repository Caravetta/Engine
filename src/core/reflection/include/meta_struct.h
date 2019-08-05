#ifndef __META_STRUCT_H__
#define __META_STRUCT_H__

#include "core_common.h"
#include "meta_base.h"

namespace Engine {

class Meta_Struct;

typedef void (*populate_meta_struct_func)( Meta_Struct& );

#define META_STRUCT_DECLARE( _struct )                                     \
     public:\
     typedef _struct __this;                                               \
     static const Engine::Meta_Struct* __s_meta_struct;                    \
     static Engine::Meta_Struct_Registrar<_struct, void> __s__registrar;   \
     static const Engine::Meta_Struct* create_meta_struct( void );         \

#define META_STRUCT_DEFINE( _struct )                                                \
     const Engine::Meta_Struct* _struct::__s_meta_struct = NULL;                              \
     Engine::Meta_Struct_Registrar<_struct, void> _struct::__s__registrar(#_struct); \
     const Engine::Meta_Struct* _struct::create_meta_struct( void )                           \
     {                                                                               \
          Engine::Meta_Struct::create<_struct>(__s_meta_struct, #_struct, NULL);     \
          return __s_meta_struct;                                                    \
     }                                                                               \

#define META_DERIVED_STRUCT_DECLARE( _struct, _base )
#define META_DERIVED_STRUCT_DEFINE( _struct, _base )

// Empty base struct for type deduction
namespace Reflection {
struct Struct {};
} // end namespace Reflection

class Meta_Struct : public Meta_Base {
protected:
     Meta_Struct( void );
     ~Meta_Struct( void );

public:
     const Meta_Struct*            __base_struct;
     populate_meta_struct_func     __populate_func;

     META_BASE_DERIVED( Meta_Base_ID::META_STRUCT_ID, Meta_Struct, Meta_Base );

     static Meta_Struct* create( void );
     template<class T> static void create( Meta_Struct const*& meta_struct, const char* name, const char* base_name );
     template<class T> static void create( const char* name, const char* base_name,
                                           populate_meta_struct_func func, Meta_Struct* info );

     virtual void meta_register( void ) const override;
     virtual void meta_unregister( void ) const override;

     void add_derived_struct( const Meta_Struct* derived ) const;
};

template<class Class_T, class Base_T>
class Meta_Struct_Registrar : public Meta_Base_Registrar {
public:
     Meta_Struct_Registrar( const char* name );
     ~Meta_Struct_Registrar( void );

     virtual void meta_register( void );
     virtual void meta_unregister( void );
};

template< class Class_T >
class Meta_Struct_Registrar<Class_T, void> : public Meta_Base_Registrar {
public:
     Meta_Struct_Registrar( const char* name );
     ~Meta_Struct_Registrar( void );

     virtual void meta_register( void );
     virtual void meta_unregister( void );
};

} // end namespace Engine

#include "meta_struct.inl"

#endif //__META_STRUCT_H__
