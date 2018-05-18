#if !defined(COMPONENT_MANAGER_H)

#include <vector>
#include <utility>
#include <type_traits>
#include <bitset>
#include "../core_common.h"
#include "component.h"

namespace core {

#define COMP_VEC_SIZE 50

    static uint64_t current_type_idx = 0;

    template <typename T>
    struct type_idx_info
    {
        static uint64_t idx;
    };
    template <typename T>
    uint64_t type_idx_info<T>::idx{current_type_idx++};

    template <typename TBase, typename T>
    inline constexpr auto isBaseOf() noexcept
    {
        return std::is_base_of<TBase, T>();
    }

    class Component_Manager {
    private:
        CORE_API static Component_Manager* instance;
        std::vector<char*> components;
        void init();
    public:
        static Component_Manager* get_instance();
        uint64_t get_max_components();
        template<typename T> void register_component();
        template<typename T> void set_component( uint64_t entity_index, T component );
        template<typename T> T get_component( uint64_t entity_index ); //TODO: need to change from using entity index to using entity handle
        template<typename T> uint64_t get_component_index();
        template<typename T> uint64_t id();
        template<typename T> bool valid_component();
    };


void Component_Manager::init()
{
    components.resize(current_type_idx);
}

Component_Manager* Component_Manager::get_instance()
{
    if ( instance == NULL ) {
        LOG("Initializing Component_Manager");
        instance = new Component_Manager;
        instance->init();
    }
    return instance;
}

uint64_t Component_Manager::get_max_components()
{
    return current_type_idx;
}

template<typename T>
uint64_t Component_Manager::get_component_index()
{
    return type_idx_info<T>::idx;
}

template<typename T>
uint64_t Component_Manager::id()
{
    return type_idx_info<T>::idx;
}

template<typename T>
bool Component_Manager::valid_component()
{
    if ( components[type_idx_info<T>::idx] != NULL ) {
        return true;
    } else {
        return false;
    }
}

template<typename T>
void Component_Manager::register_component()
{
    if ( components[type_idx_info<T>::idx] == NULL ) {
        components[type_idx_info<T>::idx] = (char*)(new std::vector<T>(COMP_VEC_SIZE));
    }
    LOG("Registered Component: " << typeid(T).name() << " with ID: " << type_idx_info<T>::idx);
}

template<typename T>
void Component_Manager::set_component( uint64_t entity_index, T new_component )
{
    if (components[type_idx_info<T>::idx] != NULL) {
        std::vector<T>* component = (std::vector<T>*)components[type_idx_info<T>::idx];
        component->at(entity_index) = new_component;
    } else {
        LOG_ERROR("Component has not been enabled");
    }
}

template<typename T>
T Component_Manager::get_component( uint64_t entity_index )
{
    std::vector<T>* component = (std::vector<T>*)components[type_idx_info<T>::idx];
    return component->at(entity_index);
}

} // end namespace core

#define COMPONENT_MANAGER_H
#endif
