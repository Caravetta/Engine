#ifndef __MOTION_SYSTEM_H__
#define __MOTION_SYSTEM_H__

//#include "../core/core.h"

class Motion_System : public core::System {
public:
    Motion_System();
    void init();
    void update();
    void shutdown();
};

#endif
