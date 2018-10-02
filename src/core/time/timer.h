#ifndef __TIMER_H__
#define __TIMER_H__

#include "../core_common.h"

namespace core {

    class CORE_API Timer {
    private:
        DWORD last_time;
        float delta_time;

    public:
        Timer();
        void update();
        float get_delta();
    };

} //end namespace core

#endif //__TIMER_H__
