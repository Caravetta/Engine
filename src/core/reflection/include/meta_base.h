#ifndef __META_BASE_H__
#define __META_BASE_H__

#include <map>
#include <string>
#include "core_common.h"

namespace Engine {

#define META_BASE( _id, _type )                                            \
     typedef _type __this;                                                 \
     const static Meta_Base_ID __id = _id;                                 \
     virtual Meta_Base_ID get_meta_id( void ) const { return _id; }        \
     virtual bool is_a( Meta_Base_ID id ) const { return _id == id; }

#define META_BASE_DERIVED( _id, _type, _base )                                                 \
     typedef _type __this;                                                                     \
     typedef _base __base;                                                                     \
     const static Meta_Base_ID __id = _id;                                                     \
     virtual Meta_Base_ID get_meta_id( void ) const { return _id; }                            \
     virtual bool is_a( Meta_Base_ID id ) const { return (_id == id || _base::is_a(_id)); }

enum Meta_Base_ID {
     INVALID_ID = -1,
     META_BASE_ID,
     META_STRUCT_ID,
     ID_COUNT, /* should always be at end of enum */
};

extern const char* Meta_Base_ID_Strings[ Meta_Base_ID::ID_COUNT ];

class Meta_Base {
protected:
     mutable std::map< std::string, std::string > __properties;

public:
     mutable const void* __tag;
     const char*         __name;
     uint32_t            __size;

     META_BASE( Meta_Base_ID::META_BASE_ID, Meta_Base );

     Meta_Base( void );
     virtual ~Meta_Base( void );

     virtual void meta_register( void ) const;
     virtual void meta_unregister( void ) const;

     template<class T> inline Rc_t set_property( const std::string& key, const T& value ) const;
     template<class T> inline Rc_t get_property( const std::string& key, T& value ) const;
     inline std::string get_property( const std::string& key ) const;
};

template<typename T>
T* reflection_cast( Meta_Base* info )
{
     return (info && info->is_a( T::__id )) ? (T*)(info) : NULL;
}

template<typename T>
const T* reflection_cast( Meta_Base* info )
{
     return (info && info->is_a( T::__id )) ? (T*)(info) : NULL;
}


enum Registrar_Base_Types {
     META_STRUCT_TYPE,
     TYPE_COUNT,
};

extern const char* Registrar_Base_Types_Strings[ Registrar_Base_Types::TYPE_COUNT ];

class Meta_Base_Registrar {
private:
     const char*                   __name;
     Meta_Base_Registrar*          __next;
     static Meta_Base_Registrar*   __s_head[Registrar_Base_Types::TYPE_COUNT];
     static Meta_Base_Registrar*   __s_tail[Registrar_Base_Types::TYPE_COUNT];

public:
     Meta_Base_Registrar( const char* name );

     virtual void meta_register( void ) = 0;
     virtual void meta_unregister( void ) = 0;

     static void add_to_list( Registrar_Base_Types type, Meta_Base_Registrar* registrar );
     static void remove_from_list( Registrar_Base_Types type, Meta_Base_Registrar* registrar );
     static void register_type( Registrar_Base_Types type );
     static void unregister_type( Registrar_Base_Types type );
     static void add_type_to_registry( Meta_Base* type );
     static void remove_type_from_registry( const Meta_Base* type );
};

} // end namespace Engine

#include "meta_base.inl"

#endif //__META_BASE_H__
