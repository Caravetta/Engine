#include <Windows.h>
#include "timer.h"

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
        last_time = timeGetTime();
    }

    DWORD current_time = timeGetTime();

    delta_time = (current_time - last_time) * 0.001f;
    last_time = current_time;
}

float Timer::get_delta()
{
    return delta_time;
}

} //end namespace core
