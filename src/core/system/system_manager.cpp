#include "system_manager.h"
#include "../entity_system/entity_manager.h"

namespace core {
namespace System_Manager{

std::vector<System*> systems;

void System_Manager::init_systems( void )
{
    for ( uint32_t i = 0; i < systems.size(); i++ ) {
        systems[i]->init();
    }
}

void System_Manager::update_systems( void )
{
    START_TIME_BLOCK( update_systems );
    for ( uint32_t i = 0; i < systems.size(); i++ ) {
        if ( systems[i]->pre_update() ) {
            systems[i]->update();
        }
    }
    END_TIME_BLOCK( update_systems );
}

void System_Manager::shutdown_systems( void )
{
    for ( uint32_t i = 0; i < systems.size(); i++ ) {
        systems[i]->shutdown();
    }
}

void register_generic_system( System* system )
{
    systems.push_back(system);
}

std::vector<System*>* get_system_vec( void )
{
    return &systems;
}

} //end namespace System_Manager
} //end namespace core

