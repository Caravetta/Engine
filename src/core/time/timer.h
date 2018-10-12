#if !defined(TIMER_H)

#include "../core_common.h"

#ifdef LINUX
#define NOW_T uint64_t
#else
#define NOW_T DWORD
#endif

namespace core {

    class CORE_API Timer {
    private:
        NOW_T last_time;
        float delta_time;

    public:
        Timer();
        void update();
        float get_delta();
    };

} //end namespace core

#define TIMER_H
#endif
