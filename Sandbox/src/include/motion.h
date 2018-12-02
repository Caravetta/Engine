#ifndef __MOTION_H__
#define __MOTION_H__

#include <Engine.h>

struct Motion {
    Engine::Vector3f velocity;
    Engine::Vector3f acceleration;
};

struct Motion_System : public Engine::System {
    Motion_System();
    void init();
    void update();
    void shutdown();
};

#endif
