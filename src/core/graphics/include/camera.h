#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "core_common.h"
#include "engine_math.h"
#include "ecs.h"

namespace Engine {

struct Camera {
     Matrix4f  perspective;
     Matrix4f  view;
     Transform transform;
};

void set_active_camera( Camera& camera );
Camera& get_active_camera( void );

} // end namespace Engine

#endif //__CAMERA_H__
