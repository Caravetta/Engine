#ifndef __TIMER_H__
#define __TIMER_H__

#include "../core_common.h"

namespace core {

    class CORE_API Timer {
    private:
        DWORD last_time;
        float delta_time;
        std::chrono::steady_clock::time_point last;
    public:
        Timer();
        void update();
        float get_delta();
        float get_delta_ms();
    };

} //end namespace core

#endif //__TIMER_H__
