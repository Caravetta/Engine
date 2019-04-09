#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include "core_common.h"
#include "return_codes.h"
#include "base_generated_component_info.h"

#ifndef INTERNAL
//#include "generated_component_info.h"
#endif

namespace Engine {

#define TAG_ID( var ) TAG_GEN_ID_ ## var

#define INVALID_COMPONENT 0
#define INVALID_TAG 0

typedef uint32_t Component_ID;
typedef Rc_t (*component_create_function)( uint8_t* memory );
typedef Rc_t (*component_copy_function)( uint8_t* source, uint8_t* dest );

enum Component_Type {
    COMPONENT_TYPE,
    TAG_TYPE,
    UNDEFINED_COMPONENT_TYPE,
};

struct Component_Info {
    Component_Type              type;
    component_create_function   create_function;
    component_copy_function     copy_function;
    size_t                      size;
};

Rc_t init_component_system( void );
Rc_t register_component_info( const Component_ID id, const Component_Info info );
component_create_function get_component_create( const Component_ID id );
component_copy_function get_component_copy( const Component_ID id );
uint64_t get_component_size( const Component_ID id );
Component_Type get_component_type( const Component_ID id );
template<typename T> Rc_t component_create( uint8_t* memory );
template<typename T> Rc_t component_copy( uint8_t* source, uint8_t* dest );
//template<typename T> Component_ID get_component_id( void );
//template<typename T> uint32_t get_tag_id( void );

template<typename T>
Rc_t component_create( uint8_t* memory )
{
    new (memory) T;
    return SUCCESS;
}

template<typename T>
Rc_t component_copy( uint8_t* source, uint8_t* dest )
{
    T* source_p = (T*)source;
    T* dest_p = (T*)dest;

    *dest_p = *source_p;

    return SUCCESS;
}

#if 0
template<typename T>
Component_ID get_component_id( void )
{
    return COMP_ID( T );
}
#endif

#if 0
template<typename T>
uint32_t get_tag_id( void )
{
    return Type_Idx_Info<T>::id;
}
#endif

} // end namespace Engine

#endif // __COMPONENT_H__
