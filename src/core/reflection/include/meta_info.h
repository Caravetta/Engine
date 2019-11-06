#ifndef __META_INFO_H__
#define __META_INFO_H__

#include <vector>
#include <unordered_map>
#include "core_common.h"
#include "meta_field.h"

namespace Engine {

class Meta_Info;

typedef void (*populate_meta_info_func)( Meta_Info& );

#define META_INFO_DECLARE( _type )                               \
     public:                                                     \
     static const Engine::Meta_Info* __s_meta_info;              \
     static Engine::Meta_Info_Registrar<_type> __s_registrar;   \
     static const Engine::Meta_Info* create_meta_info( void );   \

#define META_INFO_DEFINE( _type )                                          \
     const Engine::Meta_Info* _type::__s_meta_info = NULL;                 \
     Engine::Meta_Info_Registrar<_type> _type::__s_registrar;     \
     const Engine::Meta_Info* _type::create_meta_info( void )        \
     {\
          Engine::Meta_Info::create<_type>(__s_meta_info, #_type);         \
          return __s_meta_info;                                            \
     } \

class Meta_Info {
protected:
     Meta_Info( void );
     //~Meta_info( void );

public:
     const char*              __name;
     uint32_t                 __size;
     populate_meta_info_func  __populate_func;
     std::vector<Meta_Field>  __fields;

     static Meta_Info* create( void );
     void populate_info( void );
     template<class T> static void create( Meta_Info const*& meta_info, const char* name );
     template<class T> static void create( const char* name, populate_meta_info_func func, Meta_Info* info );
     template<class Struct_T, class Field_T> void add_field( Field_T Struct_T::* field, const char* name,
                                                              uint32_t flags = 0 );

};

class Meta_Info_Base_Registrar {
public:
     Meta_Info_Base_Registrar* __next;
     static Meta_Info_Base_Registrar* __s_head;
     static Meta_Info_Base_Registrar* __s_tail;
     static std::unordered_map<uint32_t, const Meta_Info*> meta_map;

     Meta_Info_Base_Registrar( void );
     ~Meta_Info_Base_Registrar( void );

     virtual void meta_info_register( void ) = 0;

     static void add_to_list( Meta_Info_Base_Registrar* registrar );
     static void add_meta_info( const Meta_Info* meta_info );
     static void register_meta_info( void );
};

template<class T>
class Meta_Info_Registrar : public Meta_Info_Base_Registrar {
public:
     Meta_Info_Registrar( void );
     ~Meta_Info_Registrar( void );

     virtual void meta_info_register( void );
};

} // end namespace Engine

#include "meta_info.inl"

#endif //__META_INFO_H__

