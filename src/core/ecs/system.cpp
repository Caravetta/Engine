#include <vector>
#include "system.h"
#include "timer.h"

namespace Engine {

struct System_Manager {
     std::vector<System*> systems;
};

System_Manager* system_manager = NULL;

Rc_t init_system_manager( void )
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

     Engine::Timer system_time;

     for ( size_t ii = 0; ii < systems.size(); ii++ ) {
          //system_time.start();
          systems[ii]->update(time_step);
          //float dt = (float)system_time.elapsed_milli_sec();
          //LOG("SYS Time %f", dt);
     }
}

void shutdown_systems( void )
{
     std::vector<System*>& systems = system_manager->systems;

     Engine::Timer system_time;

     for ( size_t ii = 0; ii < systems.size(); ii++ ) {
          system_time.start();
          systems[ii]->shutdown();
          float dt = (float)system_time.elapsed_milli_sec();
          LOG("SYS Time %f", dt);
     }
}

} // end namespace Engine

