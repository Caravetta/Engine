#ifndef __SCENE_CAMERA_H__
#define __SCENE_CAMERA_H__

#include "engine_core.h"
#include "gtx/string_cast.hpp"
#include "gtc/type_ptr.hpp"
#include "gtx/quaternion.hpp"

class Scene_Camera : public Engine::System {
public:
     void init( void );
     void update( float time_step );
     void shutdown( void );

private:
     void pan( float x_delta, float y_delta );
     void zoom( float delta );
     void rotate( float x_delta, float y_delta );
     glm::quat orientation( void );
     glm::vec3 calc_position( void );
     glm::vec3 forward_direction( void );
     glm::vec3 right_direction( void );
     glm::vec3 up_direction( void );
     glm::vec3 pan_speed( void );
     float zoom_speed( void );

     Engine::Camera scene_camera;
     glm::vec3 position;
     glm::vec3 focal_point;
     float distance;
     float width;
     float height;
     float pitch;
     float yaw;
     float cur_mouse_x;
     float cur_mouse_y;
};

#endif //__SCENE_CAMERA_H__
