#ifndef __SYSTEMS_H__
#define __SYSTEMS_H__

#include <Engine.h>

struct Player_System : public Engine::System {
    Player_System();
    void init();
    void update();
    void shutdown();
};

struct Bullet_Spawn_System : public Engine::System {
    Bullet_Spawn_System();
    void init();
    void update();
    void shutdown();
};

struct Bullet_Motion_System : public Engine::System {
    Bullet_Motion_System();
    void init();
    void update();
    void shutdown();
};

#endif //__SYSTEMS_H__
