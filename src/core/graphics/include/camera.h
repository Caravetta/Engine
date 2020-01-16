#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "core_common.h"
#include "engine_math.h"
#include "ecs.h"
#include "window.h"

namespace Engine {

struct Camera {
     META_INFO_DECLARE( Camera );

     static void populate_meta_info_func( Engine::Meta_Info& meta_info );

     Matrix4f  perspective;
     Matrix4f  view;
     Transform transform;
     Window*   window; //TODO(JOSH): Once event system is in place this should be removed //REMOVE
};

void set_active_camera( Camera& camera );
Camera& get_active_camera( void );

} // end namespace Engine

#endif //__CAMERA_H__
