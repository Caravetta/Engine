#ifndef __TEXT_RENDER_SYSTEM_H__
#define __TEXT_RENDER_SYSTEM_H__

//#include "../core/core.h"

class Text_Render_System : public core::System {
public:
    Text_Render_System();
    void init();
    void update();
    void shutdown();
};

#endif //__TEXT_RENDER_SYSTEM_H__
