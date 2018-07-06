#if !defined(TEXT_RENDER_SYSTEM_H)

#include "../core/core.h"

class Text_Render_System : public core::System {
public:
    Text_Render_System();
    void init();
    void update();
    void shutdown();
};

#define TEXT_RENDER_SYSTEM_H
#endif
