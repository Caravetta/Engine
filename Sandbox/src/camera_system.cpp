#include "systems.h"
#include "components.h"

Camera_System::Camera_System()
{
    name = "Camera_System";
    add_component<Camera_Info>();
}

void Camera_System::init()
{

}

void Camera_System::update()
{
    std::vector<Camera_Info*>* camera_info_vec = get_data_vec<Camera_Info>();

    Camera_Info* camera_info;

    float dt = Engine::get_delta_time();

    for ( uint32_t ii = 0; ii < entity_count; ++ii ) {
        camera_info = camera_info_vec->at(ii);

        if ( camera_info->camera_type == MAIN_CAM_TYPE ) {

            if ( Engine::is_key_pressed(Engine::KEY_R) ) {
                camera_info->camera.transform.rotation.y += 2 * dt;
            } else if ( Engine::is_key_pressed(Engine::KEY_F) ) {
                camera_info->camera.transform.rotation.y += -2 * dt;
            }

            Engine::generate_perspective_matrix(&camera_info->camera);
            Engine::generate_FPS_view_matrix(&camera_info->camera);
        }
    }
}

void Camera_System::shutdown()
{

}
