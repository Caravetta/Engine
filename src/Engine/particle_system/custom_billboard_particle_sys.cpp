#include "Engine.h"

namespace Engine {

Custom_Billboard_Particle_System::Custom_Billboard_Particle_System()
{
     add_component(TRANSFORM_COMP);
     add_component(CUSTOM_BILLBOARD_PARTICLE_EMITTER_COMP);
     add_component(MESH_HANDLE_COMP);
}

void Custom_Billboard_Particle_System::init()
{

}

void Custom_Billboard_Particle_System::update()
{

}

void Custom_Billboard_Particle_System::shutdown()
{

}

} // end namespace Engine
