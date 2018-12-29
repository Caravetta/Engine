#include "systems.h"
#include "components.h"
#include "input_tracker.h"

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
    std::vector<Player*>* player_vec = get_data_vec<Player>();

    Engine::Transform* transform;
    Player* player;

    float dt = Engine::get_delta_time();

    for( uint32_t ii = 0; ii < entity_count; ++ii ) {

        transform = transform_vec->at(ii);

        if (is_key_pressed(Input_Tracker::W_KEY_STATE)) {
            transform->position.z = transform->position.z + (-1 * dt);
        } else if (is_key_pressed(Input_Tracker::S_KEY_STATE)) {
            transform->position.z = transform->position.z + (1 * dt);
        }

        if (is_key_pressed(Input_Tracker::A_KEY_STATE)) {
            transform->position.x = transform->position.x + (-1 * dt);
        } else if (is_key_pressed(Input_Tracker::D_KEY_STATE)) {
            transform->position.x = transform->position.x + (1 * dt);
        }
    }
}

void Player_System::shutdown()
{

}
