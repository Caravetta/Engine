#include <algorithm>
#include "scene_camera.h"
#include "editor_context.h"

void Scene_Camera::init( void )
{
     Editor_Context* editor_context = Editor_Context::get_instance();
     scene_camera.window = editor_context->window;

     width = (float)scene_camera.window->width();
     height = (float)scene_camera.window->height();

     position = glm::vec3(0, 0, 1);
     focal_point = glm::vec3(0, 0, 0);

     pitch = 0;
     yaw = 0;

     distance = glm::distance(position, focal_point);

     glm::mat4 per_test = glm::perspectiveFov(glm::radians(45.0f), width, height, 0.1f, 1000.0f);

     const float *pSource = (const float*)glm::value_ptr(per_test);

     float* per_array = (float*)&scene_camera.perspective;
     for ( size_t ii = 0; ii < 16; ii++ ) {
          per_array[ii] = pSource[ii];
     }

     glm::mat4 view_test = glm::inverse(glm::translate(glm::mat4(1.0f), position));

     const float *pSource1 = (const float*)glm::value_ptr(view_test);

     float* view_array = (float*)&scene_camera.view;
     for ( size_t ii = 0; ii < 16; ii++ ) {
          view_array[ii] = pSource1[ii];
     }

     editor_context->scene_camera = &scene_camera;

     Engine::set_active_camera(scene_camera);

}

void Scene_Camera::update( float time_step )
{
     Editor_Context* editor_context = Editor_Context::get_instance();

     if ( width != (float)scene_camera.window->width() ||
          height != (float)scene_camera.window->height() ) {

          width = (float)scene_camera.window->width();
          height = (float)scene_camera.window->height();

          glm::mat4 per_test = glm::perspectiveFov(glm::radians(45.0f), width, height, 0.1f, 1000.0f);

          const float *pSource = (const float*)glm::value_ptr(per_test);

          float* per_array = (float*)&scene_camera.perspective;
          for ( size_t ii = 0; ii < 16; ii++ ) {
               per_array[ii] = pSource[ii];
          }
     }

     float mouse_x = Engine::mouse_x_position();
     float mouse_y = Engine::mouse_y_position();

     float delta_x = mouse_x - cur_mouse_x;
     float delta_y = mouse_y - cur_mouse_y;

     delta_y *= 0.01f * -1.0f;
     delta_x *= 0.01f * -1.0f;


     cur_mouse_x = mouse_x;
     cur_mouse_y = mouse_y;

     if ( Engine::is_key_pressed(Engine::KEY_W) ) {
          zoom(delta_y);
     }

     if ( Engine::is_key_pressed(Engine::KEY_A) ) {
          pan(-delta_x, delta_y);
     }

     if ( Engine::is_key_pressed(Engine::KEY_D) ) {
          rotate(-delta_x, delta_y);
     }

     position = calc_position();

     glm::quat orient = orientation();
     glm::mat4 view_test = glm::translate(glm::mat4(1.0f), position) * glm::toMat4(orient);

     view_test = glm::inverse(view_test);

     const float *pSource1 = (const float*)glm::value_ptr(view_test);

     float* view_array = (float*)&scene_camera.view;
     for ( size_t ii = 0; ii < 16; ii++ ) {
          view_array[ii] = pSource1[ii];
     }

}

void Scene_Camera::shutdown( void )
{
     // nothing to do
}

void Scene_Camera::pan( float x_delta, float y_delta )
{
     glm::vec3 speed = pan_speed();

     focal_point += -right_direction() * x_delta * speed.x * distance;
     focal_point += up_direction() * y_delta * speed.y * distance;
}

void Scene_Camera::zoom( float delta )
{
     distance -= delta * zoom_speed();

     if ( distance < 1.0f ) {
          focal_point += forward_direction();
          distance = glm::distance(position, focal_point);
     }
}

void Scene_Camera::rotate( float x_delta, float y_delta )
{
     float yaw_sign = up_direction().y < 0 ? -1.0f : 1.0f;
     yaw += yaw_sign * x_delta * 0.8f;
     pitch += y_delta * 0.8f;
}

glm::quat Scene_Camera::orientation( void )
{
     return glm::quat(glm::vec3(-pitch, -yaw, 0.0f));
}

glm::vec3 Scene_Camera::calc_position( void )
{
     return focal_point - forward_direction() * distance;
}

glm::vec3 Scene_Camera::forward_direction( void )
{
     return glm::rotate(orientation(), glm::vec3(0.0f, 0.0f, -1.0f));
}

glm::vec3 Scene_Camera::right_direction( void )
{
     return glm::rotate(orientation(), glm::vec3(1.0f, 0.0f, 0.0f));
}

glm::vec3 Scene_Camera::up_direction( void )
{
     return glm::rotate(orientation(), glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::vec3 Scene_Camera::pan_speed( void )
{
     float x = std::min(width / 1000.0f, 2.4f); // max = 2.4f
     float xFactor = 0.0366f * (x * x) - 0.1778f * x + 0.3021f;

     float y = std::min(height / 1000.0f, 2.4f); // max = 2.4f
     float yFactor = 0.0366f * (y * y) - 0.1778f * y + 0.3021f;

     return glm::vec3(xFactor, yFactor, 0);
}

float Scene_Camera::zoom_speed( void )
{
     float dis = distance * 0.2f;
     dis = std::max(dis, 0.0f);
     float speed = dis * dis;
     speed = std::min(speed, 100.0f); // max speed = 100

     return speed;
}

