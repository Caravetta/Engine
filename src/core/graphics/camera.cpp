#include "camera.h"

namespace Engine {

Camera* active_camera = NULL;

META_INFO_DEFINE( Camera );

void Camera::populate_meta_info_func( Engine::Meta_Info& meta_info )
{
     meta_info.add_field(&Camera::transform, "transform");
}

void set_active_camera( Camera& camera )
{
     active_camera = &camera;
}

Camera& get_active_camera( void )
{
     return *active_camera;
}

} // end namespace Engine

