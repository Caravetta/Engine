#include "systems.h"
#include "components.h"

Player_System::Player_System()
{
    name = "Player_System";
    add_component<Engine::Transform>();
    add_component<Player>();
}

void Player_System::init()
{

}

void Player_System::update()
{
    std::vector<Engine::Transform*>* transform_vec = get_data_vec<Engine::Transform>();

    Engine::Transform* transform;

    float dt = Engine::get_delta_time();

    for ( uint32_t ii = 0; ii < entity_count; ++ii ) {

        transform = transform_vec->at(ii);

        if ( Engine::is_key_pressed(Engine::KEY_W) ) {
            transform->position.z = transform->position.z + (-1 * dt);
        } else if ( Engine::is_key_pressed(Engine::KEY_S) ) {
            transform->position.z = transform->position.z + (1 * dt);
        }

        if ( Engine::is_key_pressed(Engine::KEY_A) ) {
            transform->position.x = transform->position.x + (-1 * dt);
        } else if ( Engine::is_key_pressed(Engine::KEY_D) ) {
            transform->position.x = transform->position.x + (1 * dt);
        }

        if ( Engine::is_key_pressed(Engine::KEY_C) ) {
            transform->position.y = transform->position.y + (1 * dt);
        } else if ( Engine::is_key_pressed(Engine::KEY_V) ) {
            transform->position.y = transform->position.y + (-1 * dt);
        }

        if ( Engine::is_key_pressed(Engine::KEY_F) ) {
            //Engine::rotate_active_camera( 0, 2 * dt);
        }
        if ( Engine::is_key_pressed(Engine::KEY_R) ) {
            //Engine::rotate_active_camera( 0, -2 * dt);
        }
    }
}

void Player_System::shutdown()
{

}
