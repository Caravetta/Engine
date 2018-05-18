#include "system_manager.h"
#include "../entity_system/entity_manager.h"

namespace core {

#define SYSTEM_VEC_SIZE 2

System_Manager* System_Manager::instance = NULL;

System_Manager* System_Manager::get_instance()
{
    if ( instance == NULL ) {
        LOG("Initializing System_Manager");
        instance = new System_Manager;
        instance->init();
    }

    return instance;
}

void System_Manager::init()
{
//    systems.resize(SYSTEM_VEC_SIZE);
}

void System_Manager::register_entity( Entity entity )
{
    //looks to see what systems care about this entity and adds it to there update list
    Entity_Manager* entity_manager = Entity_Manager::get_instance();

    for ( int i = 0; i < systems.size(); i++ ) {
        bool should_add = false;
        System::system_config_t system_config = systems[i]->get_system_config();

        for ( int j = 0; j < system_config.components.size(); j++ ) {
            if ( entity_manager->is_component_set(entity, system_config.components[j].component_id) ) {
                should_add = true;
            } else {
                should_add = false;
                break;
            }
        }

        if ( should_add == true ) {
            systems_info[i].entities.push_back(entity);
            systems_info[i].entity_map.insert({ entity.id, (systems_info[i].entities.size() - 1) });
        }
    }
}

void System_Manager::deregister_entity( Entity entity )
{
    //TODO: The way we clean up needs to be alot better this is REALLY SLOW
    //loops through all the systems and removes the entity if it is present.
    for ( int i = 0; i < systems.size(); i++ ) {
        std::unordered_map<uint64_t, uint64_t>::const_iterator ele = systems_info[i].entity_map.find(entity.id);
        if ( ele != systems_info[i].entity_map.end() ) {
            //this system is using this entity.
            systems_info[i].entities.erase(systems_info[i].entities.begin() + ele->second);
            systems_info[i].entity_map.clear();
            for ( int j = 0; j < systems_info[i].entities.size(); j++ ) {
                systems_info[i].entity_map.insert({ systems_info[i].entities[j].id, j });
            }
        }
    }
}

void System_Manager::init_systems()
{
    for ( uint32_t i = 0; i < systems.size(); i++ ) {
        systems[i]->init();
    }
}

void System_Manager::update_systems()
{
    for ( uint32_t i = 0; i < systems.size(); i++ ) {
        systems[i]->set_entity_vector(&systems_info[i].entities);
        systems[i]->update();
    }
}

void System_Manager::shutdown_systems()
{
    for ( uint32_t i = 0; i < systems.size(); i++ ) {
        systems[i]->shutdown();
    }
}

} //end namespace core
