#if !defined(CUBE_ORBIT_SYSTEM_H)

#include "../core/core.h"

class Cube_Orbit_System : public core::System {
public:
    Cube_Orbit_System();
    void init();
    void update();
    void shutdown();
};

#define CUBE_ORBIT_SYSTEM_H
#endif
