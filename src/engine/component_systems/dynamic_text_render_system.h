#ifndef __DYNAMIC_TEXT_RENDER_SYSTEM_H__
#define __DYNAMIC_TEXT_RENDER_SYSTEM_H__

#include "../core/core.h"

class Dynamic_Text_Render_System : public core::System {
public:
    Dynamic_Text_Render_System();
    void init();
    void update();
    void shutdown();
};

#endif //__DYNAMIC_TEXT_RENDER_SYSTEM_H__
