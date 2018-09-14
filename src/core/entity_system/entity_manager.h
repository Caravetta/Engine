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
#include "entity_archetype_manager.h"

namespace core {

    class Entity_Manager {
    private:
        CORE_API static Entity_Manager* instance;
        Component_Manager* component_manager;
        Entity_Archetype_Manager* archetype_manager;
        uint32_t next_entity_idx;
        std::vector<Entity> entities;
        void init();
    public:
        static Entity_Manager* get_instance();
        Entity get_new_entity( std::string archetype_name );
        Entity get_new_entity( Entity_Archetype* archetype );
	    UhRC_t delete_entity( Entity entity );
        bool is_valid_entity( Entity entity );
        UhRC_t register_archetype( Entity_Archetype archetype, std::string archetype_name );

        template<typename T> UhRC_t add_component( Entity entity );
        template<typename T> UhRC_t remove_component( Entity entity );
        template<typename T> T* get_component( Entity entity );
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
    archetype_manager = Entity_Archetype_Manager::get_instance();
    component_manager = Component_Manager::get_instance();
}

Entity Entity_Manager::get_new_entity( std::string archetype_name )
{
    entities[next_entity_idx].id.set_active();
    uint32_t return_index = next_entity_idx;
    next_entity_idx++;
    Entity_Archetype_Manager::get_instance()->add_entity( entities[return_index], archetype_name );
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
        //TODO: JOSH need to remove entity from archetype.
        return SUCCESS;
    }

    return ERROR_INVALID_ENTITY;
}

void Entity_Manager::resize_entities()
{
    //TODO: JOSH need to make resize more robust
    uint64_t max_components = Component_Manager::get_instance()->get_max_components();
    uint32_t max_index = (uint32_t)entities.size();
    entities.resize(entities.size() + 1000);

    for ( ; max_index < entities.size(); max_index++ ) {
        entities[max_index].id.set_inactive();
        entities[max_index].id.set_index(max_index);
    }

}

UhRC_t Entity_Manager::register_archetype( Entity_Archetype archetype, std::string archetype_name )
{
    return Entity_Archetype_Manager::get_instance()->register_archetype(archetype, archetype_name);
}

template<typename T>
UhRC_t Entity_Manager::remove_component( Entity entity )
{
    uint32_t index = entity.id.get_index();
    if ( entity.id == entities[index].id ) {
        //TODO: JOSH need to implement remove component
    }
    return ERROR_INVALID_ENTITY;
}

template<typename T>
UhRC_t Entity_Manager::add_component( Entity entity )
{
    uint32_t index = entity.id.get_index();
    if ( entity.id == entities[index].id ) {
        //TODO: JOSH need to implement add component
    }
    return ERROR_INVALID_ENTITY;
}

template<typename T>
T* Entity_Manager::get_component( Entity entity)
{
    if ( is_valid_entity(entity) ) {
        return  archetype_manager->get_component_data<T>(entity);
    }

    return NULL;
}

template<typename T>
bool Entity_Manager::is_component_set( Entity entity )
{
    //TODO: JOSH need to implement

    return false
}

bool Entity_Manager::is_valid_entity( Entity entity )
{
    uint32_t index = entity.id.get_index();
    return (entity.id == entities[index].id);
}

} // end namespace core

#define ENTITY_MANAGER_H
#endif
