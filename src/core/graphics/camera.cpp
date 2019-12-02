#include "camera.h"

namespace Engine {

Camera* active_camera = NULL;

void set_active_camera( Camera& camera )
{
     active_camera = &camera;
}

Camera& get_active_camera( void )
{
     return *active_camera;
}

} // end namespace Engine

