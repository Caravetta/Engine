#if !defined(MESH_RENDER_SYSTEM_H)

//#include "../core/core.h"

class Mesh_Render_System : public core::System {
public:
    Mesh_Render_System();
    void init();
    void update();
    void shutdown();
};

#define MESH_RENDER_SYSTEM_H
#endif
