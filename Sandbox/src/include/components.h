#ifndef __COMPONENTS_H__
#define __COMPONENTS_H__

struct Player {
    uint64_t life;
};

struct Bullet_Motion {
    Engine::Vector3f velocity;
    Engine::Vector3f acceleration;
};

struct Bullet_Distance {
    float max_distance;
};

struct Bullet_Spawner {
    Engine::Vector3f offset_location;
};

#endif //__COMPONENTS_H__
