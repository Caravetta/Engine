#include "motion_system.h"
#include <cmath>


void verlet(core::Vector3f& pos, core::Vector3f& velocity, const core::Vector3f& acceleration, float delta)
{
    float halfDelta = delta * 0.5f;
    pos += velocity * halfDelta;
    velocity += acceleration * delta;
    pos += velocity * halfDelta;
}

void forestRuth(core::Vector3f& pos, core::Vector3f& velocity, const core::Vector3f& acceleration, float delta)
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
    add_component<Transform>();
    add_component<Motion_Component>();
}

void Motion_System::init()
{

}

struct job_test : public core::Job_Loop {
    std::vector<Motion_Component*>* motion_vec;
    std::vector<Transform*>* transforms;
    float delta;

    void Execute( uint64_t index ) {
        Motion_Component* motion_component = motion_vec->at(index);
        Transform* transform = transforms->at(index);
        forestRuth(transform->position, motion_component->velocity,
                   motion_component->acceleration, delta);
    }
};

void Motion_System::update()
{
    START_TIME_BLOCK(motion_System_update);

    Engine* engine = Engine::get_instance();
#if 0
    std::vector<Motion_Component*>* motion_vec = get_data_vec<Motion_Component>();
    std::vector<Transform*>* transforms = get_data_vec<Transform>();

    Motion_Component* motion_component;
    Transform* transform;

    for(int i = 0; i < entity_count; i++) {

        motion_component = motion_vec->at(i);
        transform = transforms->at(i);

        forestRuth(transform->position, motion_component->velocity,
                   motion_component->acceleration, engine->frame_time.get_delta());
    }
#endif
#if 1
    job_test job;
    job.motion_vec = get_data_vec<Motion_Component>();
    job.transforms = get_data_vec<Transform>();
    job.delta = engine->frame_time.get_delta();
    core::Job_Handle job_handle = job.Schedule(entity_count, 1000);
    while (core::Job_Manager::is_job_complete(job_handle) == false) {};
#endif
    END_TIME_BLOCK(motion_System_update);
}

void Motion_System::shutdown()
{

}
