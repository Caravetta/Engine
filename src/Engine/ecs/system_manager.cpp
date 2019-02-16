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
    for ( u32 ii = 0; ii < systems.size(); ++ii ) {
        if ( systems[ii]->pre_update() ) {
            systems[ii]->update();
        }
    }
}

void shutdown_systems( void )
{
    for ( u32 ii = 0; ii < systems.size(); ++ii ) {
        systems[ii]->shutdown();
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
} //end namespace Engine

