#if !defined(DYNAMIC_TEXT_RENDER_SYSTEM_H)

#include "../core/core.h"

class Dynamic_Text_Render_System : public core::System {
public:
    Dynamic_Text_Render_System();
    void init();
    void update();
    void shutdown();
};

#define DYNAMIC_TEXT_RENDER_SYSTEM_H
#endif
