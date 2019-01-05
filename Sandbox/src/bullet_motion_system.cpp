#include <cmath>
#include <vector>
#include "systems.h"
#include "components.h"
#include <stdio.h>

void verlet(Engine::Vector3f& pos, Engine::Vector3f& velocity, const Engine::Vector3f& acceleration, float delta)
{
    float halfDelta = delta * 0.5f;
    pos += velocity * halfDelta;
    velocity += acceleration * delta;
    pos += velocity * halfDelta;
}

void forestRuth(Engine::Vector3f& pos, Engine::Vector3f& velocity, const Engine::Vector3f& acceleration, float delta)
{
    static const float frCoefficient = 1.0f/(2.0f-pow(2.0f,1.0f/3.0f));
    static const float frComplement = 1.0f - 2.0f*frCoefficient;
    verlet(pos, velocity, acceleration, delta*frCoefficient);
    verlet(pos, velocity, acceleration, delta*frComplement);
    verlet(pos, velocity, acceleration, delta*frCoefficient);
}

Bullet_Motion_System::Bullet_Motion_System()
{
    name = "Bullet_Motion_System";
    add_component<Engine::Transform>();
    add_component<Bullet_Motion>();
    add_component<Bullet_Distance>();
    add_component<Engine::Entity>();
}


void Bullet_Motion_System::init()
{
}


void Bullet_Motion_System::update()
{
    std::vector<Bullet_Motion*>* bullet_motion_vec = get_data_vec<Bullet_Motion>();
    std::vector<Engine::Transform*>* transforms = get_data_vec<Engine::Transform>();
    std::vector<Bullet_Distance*>* bullet_distance_vec = get_data_vec<Bullet_Distance>();
    std::vector<Engine::Entity*>* bullet_id_vec = get_data_vec<Engine::Entity>();

    Bullet_Motion* bullet_motion;
    Engine::Transform* transform;
    Engine::Entity* bullet_id;
    Bullet_Distance* bullet_distance;

    float dt = Engine::get_delta_time();

    for(int i = 0; i < entity_count; i++) {

        bullet_motion = bullet_motion_vec->at(i);
        transform = transforms->at(i);
        bullet_id = bullet_id_vec->at(i);
        bullet_distance = bullet_distance_vec->at(i);

        float old_z = transform->position.z;

        forestRuth(transform->position, bullet_motion->velocity,
                   bullet_motion->acceleration, dt);

        float new_z = transform->position.z;
        float dist = 0;
        if ( new_z < old_z ) {
            dist = old_z - new_z;
        } else {
            dist = new_z - old_z;
        }

        bullet_distance->max_distance = bullet_distance->max_distance - dist;

        if ( bullet_distance->max_distance < 0 ) {
            Engine::delete_entity(*bullet_id);
        }

    }
}

void Bullet_Motion_System::shutdown()
{

}
