#include <vector>
#include "system.h"

namespace Engine {

struct System_Manager {
     std::vector<System*> systems;
};

System_Manager* system_manager = NULL;

Rc_t init_system_systems( void )
{
     Rc_t rc = SUCCESS;

     if ( system_manager == NULL ) {
          system_manager = new (std::nothrow) System_Manager;
          if ( system_manager == NULL ) {
               rc = MEMORY_ALLOC_FAILED;
          }
     }

     return rc;
}

void register_system( System* system )
{
     system_manager->systems.push_back(system);
}

void init_systems( void )
{
     std::vector<System*>& systems = system_manager->systems;

     for ( size_t ii = 0; ii < systems.size(); ii++ ) {
          systems[ii]->init();
     }
}

void update_systems( float time_step )
{
     std::vector<System*>& systems = system_manager->systems;

     for ( size_t ii = 0; ii < systems.size(); ii++ ) {
          systems[ii]->update(time_step);
     }
}

void shutdown_systems( void )
{
     std::vector<System*>& systems = system_manager->systems;

     for ( size_t ii = 0; ii < systems.size(); ii++ ) {
          systems[ii]->shutdown();
     }
}

} // end namespace Engine

