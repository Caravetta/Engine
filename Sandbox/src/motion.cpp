#include "motion.h"
#include <cmath>
#include <vector>

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

Motion_System::Motion_System()
{
    name = "Motion_System";
    add_component<Engine::Transform>();
    add_component<Motion>();
}

void Motion_System::init()
{

}

void Motion_System::update()
{
    std::vector<Motion*>* motion_vec = get_data_vec<Motion>();
    std::vector<Engine::Transform*>* transforms = get_data_vec<Engine::Transform>();

    Motion* motion_component;
    Engine::Transform* transform;

    float dt = Engine::get_delta_time();

    for(int i = 0; i < entity_count; i++) {

        motion_component = motion_vec->at(i);
        transform = transforms->at(i);

        forestRuth(transform->position, motion_component->velocity,
                   motion_component->acceleration, dt);
    }
}

void Motion_System::shutdown()
{

}
