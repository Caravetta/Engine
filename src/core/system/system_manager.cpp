#include "system_manager.h"
#include "../entity_system/entity_manager.h"

#include <ctime>
#include <ratio>
#include <chrono>

namespace core {

#define SYSTEM_VEC_SIZE 2

System_Manager* System_Manager::instance = NULL;

System_Manager* System_Manager::get_instance()
{
    if ( instance == NULL ) {
        LOG("Initializing System_Manager");
        instance = new System_Manager;
    }

    return instance;
}

void System_Manager::init_systems()
{
    for ( uint32_t i = 0; i < systems.size(); i++ ) {
        systems[i]->init();
    }
}

void System_Manager::update_systems()
{
    START_TIME_BLOCK( update_systems );
    for ( uint32_t i = 0; i < systems.size(); i++ ) {
        if ( systems[i]->pre_update() ) {
            systems[i]->update();
        }
    }
    END_TIME_BLOCK( update_systems );
}

void System_Manager::shutdown_systems()
{
    for ( uint32_t i = 0; i < systems.size(); i++ ) {
        systems[i]->shutdown();
    }
}

} //end namespace core
