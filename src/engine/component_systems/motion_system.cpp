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
    add_component<Position_Component>();
    add_component<Motion_Component>();
}

void Motion_System::init()
{

}

struct __declspec(align(16)) job_test : public core::Job_Loop {
    std::vector<Motion_Component*>* motion_vec;
    std::vector<Position_Component*>* position_vec;
    float delta;

    void Execute( uint64_t index ) {
        Motion_Component* motion_component = motion_vec->at(index);
        Position_Component* position_component = position_vec->at(index);
        forestRuth(position_component->position, motion_component->velocity,
                   motion_component->acceleration, delta);
    }
};

void Motion_System::update()
{
    START_TIME_BLOCK(motion_System_update);

    Engine* engine = Engine::get_instance();
#if 0
    std::vector<Motion_Component*>* motion_vec = get_data_vec<Motion_Component>();
    std::vector<Position_Component*>* position_vec = get_data_vec<Position_Component>();

    Motion_Component* motion_component;
    Position_Component* position_component;

    for(int i = 0; i < entity_count; i++) {

        //motion_component = get_data_at<Motion_Component>(i);
        motion_component = motion_vec->at(i);

        //position_component = get_data_at<Position_Component>(i);
        position_component = position_vec->at(i);

        forestRuth(position_component->position, motion_component->velocity,
                   motion_component->acceleration, engine->frame_time.get_delta());
    }
#endif
#if 1
    job_test job;
    job.motion_vec = get_data_vec<Motion_Component>();
    job.position_vec = get_data_vec<Position_Component>();
    job.delta = engine->frame_time.get_delta();
    core::Job_Handle job_handle = job.Schedule(entity_count, 100);
    while (core::Job_Manager::is_job_complete(job_handle) == false) {};
#endif
    END_TIME_BLOCK(motion_System_update);
}

void Motion_System::shutdown()
{

}
