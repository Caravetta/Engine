#include "timer.h"

#ifdef LINUX
#include <time.h>
NOW_T get_time(void) {
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC_RAW, &now);
    return (now.tv_sec * 1000000) + (now.tv_nsec / 1000);
}
#else
#include <Windows.h>
NOW_T get_time(void) {
    return timeGetTime();
}
#endif

namespace core {

Timer::Timer()
{
    delta_time = 0;
    last_time = 0;
}

void Timer::update()
{
    static bool initialized;
    if ( !initialized ) {
        initialized = true;
        // do the initialization part
        last_time = get_time();
    }

    NOW_T current_time = get_time();
    delta_time = (current_time - last_time) * 0.001f;
    last_time = current_time;
}

float Timer::get_delta()
{
    return delta_time;
}

} //end namespace core
