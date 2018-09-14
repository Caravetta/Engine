#if !defined(COMPONENT_MANAGER_H)

#include <vector>
#include <utility>
#include <type_traits>
#include <bitset>
#include <limits>
#include "../core_common.h"
#include "component.h"

#define NON_VALID_ID 18446744073709551615

namespace core {

    typedef UhRC_t (*component_create_function)( uint8_t* memory );

    struct component_info {
        component_create_function create_function;
        size_t size;
    };

    template <typename T>
    struct type_idx_info
    {
        static uint64_t id;
    };
    template <typename T>
    uint64_t type_idx_info<T>::id{NON_VALID_ID};

    class Component_Manager {
    private:
        CORE_API static Component_Manager* instance;
        std::vector<component_info> component_info_vec;

    public:
        static Component_Manager* get_instance();
        uint64_t get_max_components();
        uint64_t get_component_size( uint64_t component_id );
        component_create_function get_component_create( uint64_t component_id );
        template<typename T> void register_component();
        template<typename T> uint64_t id();
    };

Component_Manager* Component_Manager::get_instance()
{
    if ( instance == NULL ) {
        LOG("Initializing Component_Manager");
        instance = new Component_Manager;
    }
    return instance;
}

uint64_t Component_Manager::get_max_components()
{
    return component_info_vec.size();
}

uint64_t Component_Manager::get_component_size( uint64_t component_id )
{
    CHECK_INFO( component_id != NON_VALID_ID, "This component has not been registered" );
    return component_info_vec[component_id].size;
}

component_create_function Component_Manager::get_component_create( uint64_t component_id )
{
    CHECK_INFO( component_id != NON_VALID_ID, "This component has not been registered" );
    return component_info_vec[component_id].create_function;
}

template<typename T>
uint64_t Component_Manager::id()
{
    CHECK_INFO( type_idx_info<T>::id != NON_VALID_ID, "This component (" << typeid(T).name() << ") has not been registered" );
    return type_idx_info<T>::id;
}

template<typename T>
void Component_Manager::register_component()
{
    component_info temp_comp;
    temp_comp.create_function = component_create<T>;
    temp_comp.size = sizeof(T);
    type_idx_info<T>::id = component_info_vec.size();
    component_info_vec.push_back(temp_comp);
    LOG("Registered Component: " << typeid(T).name() << " with ID: " << type_idx_info<T>::id << " sizeof " << temp_comp.size);
}

} // end namespace core

template<typename T>
UhRC_t component_create( uint8_t* memory )
{
    new (memory) T;
    return SUCCESS;
}

#define COMPONENT_MANAGER_H
#endif
