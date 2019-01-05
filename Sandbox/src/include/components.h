#ifndef __COMPONENTS_H__
#define __COMPONENTS_H__

struct Player {
    uint64_t life;
    std::string name;
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

typedef enum {
    MAIN_CAM_TYPE,
} camera_type_t;

struct Camera_Info {
    Engine::Camera camera;
    camera_type_t camera_type;
};

#endif //__COMPONENTS_H__
