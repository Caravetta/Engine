#include "Engine.h"
#include "system_manager.h"
#include "entity_manager.h"

namespace Engine {
namespace System_Manager{

std::vector<System*> systems;

void init_systems( void )
{
    for ( uint32_t i = 0; i < systems.size(); i++ ) {
        systems[i]->init();
    }
}

void update_systems( void )
{
    START_TIME_BLOCK( update_systems );
    for ( uint32_t i = 0; i < systems.size(); i++ ) {
        if ( systems[i]->pre_update() ) {
            systems[i]->update();
        }
    }
    END_TIME_BLOCK( update_systems );
}

void shutdown_systems( void )
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

void register_generic_system( System* system )
{
    System_Manager::systems.push_back(system);
}

} //end namespace Engine

