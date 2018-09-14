#include "cube_orbit_system.h"
#include <math.h>

Cube_Orbit_System::Cube_Orbit_System()
{
    add_component<Position_Component>();
    add_component<Cube_Orbit_Component>();
}

void Cube_Orbit_System::init()
{

}

void Cube_Orbit_System::update()
{
    #if 0
    if ( entities->size() > 0 ) {
        core::Entity_Manager* enitiy_manager = Engine::get_instance()->enitiy_manager;
        core::Entity entity;

        Position_Component pos_component;
        Cube_Orbit_Component orbit_component;

        #define PI 3.14159265

        for(int i = 0; i < entities->size(); i++) {
            entity = entities->at(i);
            enitiy_manager->get_component<Position_Component>(entity, &pos_component);
            enitiy_manager->get_component<Cube_Orbit_Component>(entity, &orbit_component);

            if ( orbit_component.start_set == false ) {
                orbit_component.start_pos = pos_component.position;
                orbit_component.start_set = true;
            }

            orbit_component.time_diff += Engine::get_instance()->frame_time.get_delta();

            pos_component.position.x = orbit_component.start_pos.x + (cos(orbit_component.time_diff) * orbit_component.width);
            pos_component.position.y = orbit_component.start_pos.y + (sin(orbit_component.time_diff) * orbit_component.height);
            pos_component.position.z = orbit_component.start_pos.z + 0; //cos(orbit_component.time_diff);

            //enitiy_manager->set_component<Position_Component>(entity, pos_component);
            //enitiy_manager->set_component<Cube_Orbit_Component>(entity, orbit_component);

            Position_Component pos_component1;
            enitiy_manager->get_component<Position_Component>(entity, &pos_component1);
        }
    }
    #endif
}

void Cube_Orbit_System::shutdown()
{

}
