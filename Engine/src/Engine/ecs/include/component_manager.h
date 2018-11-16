#ifndef __COMPONENT_MANAGER_H__
#define __COMPONENT_MANAGER_H__

#include <vector>
#include <utility>
#include <type_traits>
#include <bitset>
#include <limits>
#include "core_common.h"
#include "component.h"

#define NON_VALID_ID 4294967295

template<typename T>
UhRC_t component_create( uint8_t* memory )
{
    new (memory) T;
    return SUCCESS;
}

namespace Engine {
namespace Component_Manager {

typedef UhRC_t (*component_create_function)( uint8_t* memory );

struct component_info {
    component_create_function create_function;
    size_t size;
};

template <typename T>
struct type_idx_info
{
    static uint32_t id;
};
template <typename T>
uint32_t type_idx_info<T>::id{NON_VALID_ID};

uint32_t get_max_components();
uint64_t get_component_size( uint32_t component_id );
component_create_function get_component_create( uint32_t component_id );
void register_component_info( component_info comp_info );

template<typename T>
uint32_t id()
{
    CHECK_INFO( type_idx_info<T>::id != NON_VALID_ID, "This component (" << typeid(T).name() << ") has not been registered" );
    return type_idx_info<T>::id;
}

template<typename T>
void register_component( void )
{
    component_info temp_comp;
    temp_comp.create_function = component_create<T>;
    temp_comp.size = sizeof(T);
    type_idx_info<T>::id = get_max_components();
    register_component_info(temp_comp);
    LOG("Registered Component: " << typeid(T).name() << " with ID: " << type_idx_info<T>::id << " sizeof " << temp_comp.size);
}

} // end namespace Component_Manager
} // end namespace Engine

#endif //__COMPONENT_MANAGER_H__
