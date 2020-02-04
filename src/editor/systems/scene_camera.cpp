#include <algorithm>
#include "scene_camera.h"
#include "editor_context.h"

static void glm_mat_to_engine_mat( Engine::Matrix4f& engine_mat, glm::mat4& glm_mat )
{
     const float *pSource1 = (const float*)glm::value_ptr(glm_mat);

     engine_mat.x.x = pSource1[0];
     engine_mat.x.y = pSource1[1];
     engine_mat.x.z = pSource1[2];
     engine_mat.x.w = pSource1[3];

     engine_mat.y.x = pSource1[4];
     engine_mat.y.y = pSource1[5];
     engine_mat.y.z = pSource1[6];
     engine_mat.y.w = pSource1[7];

     engine_mat.z.x = pSource1[8];
     engine_mat.z.y = pSource1[9];
     engine_mat.z.z = pSource1[10];
     engine_mat.z.w = pSource1[11];

     engine_mat.t.x = pSource1[12];
     engine_mat.t.y = pSource1[13];
     engine_mat.t.z = pSource1[14];
     engine_mat.t.w = pSource1[15];
}

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
     glm_mat_to_engine_mat(scene_camera.perspective, per_test);

     glm::mat4 view_test = glm::inverse(glm::translate(glm::mat4(1.0f), position));
     LOG("%s", glm::to_string(view_test).c_str());

     glm_mat_to_engine_mat(scene_camera.view, view_test);

     scene_camera.view.log();

     editor_context->scene_camera = &scene_camera;

     Engine::set_active_camera(scene_camera);

}

void Scene_Camera::update( float time_step )
{
#if 0
     LOG("JOSH focal_point(%f, %f, %f) position(%f, %f, %f) distance %f forward_direction(%f, %f, %f)",
          focal_point.x, focal_point.y, focal_point.z,
          position.x, position.y, position.z,
          distance,
          forward_direction().x, forward_direction().y, forward_direction().z);
#endif
     Editor_Context* editor_context = Editor_Context::get_instance();

     if ( width != (float)scene_camera.window->width() ||
          height != (float)scene_camera.window->height() ) {

          width = (float)scene_camera.window->width();
          height = (float)scene_camera.window->height();

          glm::mat4 per_test = glm::perspectiveFov(glm::radians(45.0f), width, height, 0.1f, 1000.0f);

          glm_mat_to_engine_mat(scene_camera.perspective, per_test);
     }

     float mouse_x = Engine::mouse_x_position();
     float mouse_y = Engine::mouse_y_position();

     float delta_x = mouse_x - cur_mouse_x;
     float delta_y = mouse_y - cur_mouse_y;

     delta_y *= 0.01 * -1;
     delta_x *= 0.01 * -1;


     cur_mouse_x = mouse_x;
     cur_mouse_y = mouse_y;

     if ( Engine::is_key_pressed(Engine::KEY_W) ) {
          zoom(delta_y);
     } else if ( Engine::is_key_pressed(Engine::KEY_S) ) {
          //zoom(-0.05f);
     }

     if ( Engine::is_key_pressed(Engine::KEY_A) ) {
          pan(-delta_x, delta_y);
     } else if ( Engine::is_key_pressed(Engine::KEY_D) ) {
          rotate(-delta_x, delta_y);
     }

     if ( Engine::is_key_pressed(Engine::KEY_F) ) {
          if ( editor_context->entity_selected ) {
               Engine::Entity selected_ent = editor_context->entity_manager.get_entity(editor_context->selected_entity);
               Engine::Transform* entity_transform = Engine::get_component<Engine::Transform>(selected_ent);
               if ( entity_transform != NULL ) {
                    position.x = entity_transform->position.x;
                    position.y = entity_transform->position.y;
                    position.z = entity_transform->position.z;

                    position.z += 2;


                    focal_point = position;
                    focal_point.z -= 1.0f;

                    distance = glm::distance(position, focal_point);

                    yaw = 0;
                    pitch = 0;
               }
          }
     }

     position = calc_position();

     glm::quat orient = orientation();
     glm::mat4 view_test = glm::translate(glm::mat4(1.0f), position) * glm::toMat4(orient);

     view_test = glm::inverse(view_test);

     glm_mat_to_engine_mat(scene_camera.view, view_test);
}

void Scene_Camera::shutdown( void )
{

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

