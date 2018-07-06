#if !defined(ENTITY_MANAGER_H)

#include <vector>
#include <utility>
#include <type_traits>
#include "../core_common.h"
#include "entity.h"
#include "../handle_system/handle.h"
#include "../component_system/component_manager.h"
#include "../component_system/component.h"
#include "../system/system_manager.h"

namespace core {

    class Entity_Manager {
    private:
        CORE_API static Entity_Manager* instance;
        uint32_t next_entity_idx;
        std::vector<Entity> entities;
        std::vector<char*> components_set;
        void init();
    public:
        static Entity_Manager* get_instance();
        Entity get_new_entity();
	    UhRC_t delete_entity( Entity entity );
        bool is_component_set( Entity entity, uint64_t component_idx );
        bool is_valid_entity( Entity entity );
        template<typename T> UhRC_t add_component( Entity entity );
        template<typename T> UhRC_t remove_component( Entity entity );
        template<typename T> UhRC_t set_component( Entity entity, T component);
        template<typename T> UhRC_t get_component( Entity entity, T* component );
        template<typename T> bool is_component_set( Entity entity );

    private:
        void resize_entities();

    };

Entity_Manager* Entity_Manager::get_instance()
{
    if ( instance == NULL ) {
        LOG("Initializing Entity_Manager");
        instance = new Entity_Manager;
        instance->init();
    }

    return instance;
}

void Entity_Manager::init()
{
    next_entity_idx = 0;
    resize_entities();
}

Entity Entity_Manager::get_new_entity()
{
    entities[next_entity_idx].id.set_active();
    uint32_t return_index = next_entity_idx;
    next_entity_idx++;
#if 0
    while ( entities[next_entity_idx].id.is_active() && next_entity_idx < entities.size() ) {
        next_entity_idx++;
    }
#endif
    return entities[return_index];
}

UhRC_t Entity_Manager::delete_entity( Entity entity )
{
    uint32_t index = entity.id.get_index();
    if ( entity.id.get_value() == entities[index].id.get_value() ) {
        entities[index].id.set_inactive();
        entities[index].id.increment_phase();
        if ( index < next_entity_idx ) {
            next_entity_idx = index;
        }
        System_Manager::get_instance()->deregister_entity(entity);
        return SUCCESS;
    }

    return ERROR_INVALID_ENTITY;
}

void Entity_Manager::resize_entities()
{
    //TODO: need to make resize more robust
    uint64_t max_components = Component_Manager::get_instance()->get_max_components();
    uint32_t max_index = (uint32_t)entities.size();
    entities.resize(entities.size() + 1000);
    components_set.resize(entities.size() + 1000);

    for ( ; max_index < entities.size(); max_index++ ) {
        entities[max_index].id.set_inactive();
        entities[max_index].id.set_index(max_index);
        components_set[max_index] = (char*)(new std::vector<bool>(max_components, false));
    }

}

template<typename T>
UhRC_t Entity_Manager::remove_component( Entity entity )
{
    uint32_t index = entity.id.get_index();
    if ( entity.id == entities[index].id ) {
        if ( is_component_set<T>(entity) ) {
            std::vector<bool>* current_components = (std::vector<bool>*)components_set[index];
            uint64_t comp_idx = Component_Manager::get_instance()->get_component_index<T>();
            current_components->at(comp_idx) = false;
            System_Manager::get_instance()->deregister_entity(entity); //TODO: need to fix this
            System_Manager::get_instance()->register_entity(entity);
            return SUCCESS;
        }
        return COMPONENT_NOT_SET;
    }
    return ERROR_INVALID_ENTITY;
}

template<typename T>
UhRC_t Entity_Manager::add_component( Entity entity )
{
    uint32_t index = entity.id.get_index();
    if ( entity.id == entities[index].id ) {
        if ( Component_Manager::get_instance()->valid_component<T>() ) {
            uint64_t comp_idx = Component_Manager::get_instance()->get_component_index<T>();
            std::vector<bool>* current_components = (std::vector<bool>*)components_set[index];
            current_components->at(comp_idx) = true;
            System_Manager::get_instance()->deregister_entity(entity);
            System_Manager::get_instance()->register_entity(entity);
            return SUCCESS;
        }
        return COMPONENT_NOT_SET; //TODO: Change this error to component not registered.
    }
    return ERROR_INVALID_ENTITY;
}

template<typename T>
UhRC_t Entity_Manager::set_component( Entity entity, T component )
{
    if ( is_valid_entity(entity) ) {
        if ( is_component_set<T>(entity) ) {
            Component_Manager::get_instance()->set_component<T>(entity.id.get_index(), component);
            return SUCCESS;
        }
        return ENGINE_ERROR; //TODO: Need to change this to error component not added to enitiy
    }
    return ERROR_INVALID_ENTITY;
}

template<typename T>
UhRC_t Entity_Manager::get_component( Entity entity, T* component )
{
    if ( is_valid_entity(entity) ) {
        if ( is_component_set<T>(entity) ) {
            *component = Component_Manager::get_instance()->get_component<T>(entity.id.get_index());
            return SUCCESS;
        }
        return COMPONENT_NOT_SET;
    }
    return ERROR_INVALID_ENTITY;
}

template<typename T>
bool Entity_Manager::is_component_set( Entity entity )
{
    //TODO: need to check if the entity is valid
    uint32_t index = entity.id.get_index();
    std::vector<bool>* current_components = (std::vector<bool>*)components_set[index];
    uint64_t comp_idx = Component_Manager::get_instance()->get_component_index<T>();

    return current_components->at(comp_idx);
}

bool Entity_Manager::is_component_set( Entity entity, uint64_t component_idx )
{
    //TODO: need to check if the entity is valid
    uint32_t index = entity.id.get_index();
    std::vector<bool>* current_components = (std::vector<bool>*)components_set[index];

    return current_components->at(component_idx);
}

bool Entity_Manager::is_valid_entity( Entity entity )
{
    uint32_t index = entity.id.get_index();
    return (entity.id == entities[index].id);
}

} // end namespace core

#define ENTITY_MANAGER_H
#endif
