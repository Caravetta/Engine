//#include <Windows.h>
#include "timer.h"

namespace Engine {

Timer::Timer()
{
    delta_time = 0;
    //last_time = 0;

    last = std::chrono::steady_clock::now();
}

void Timer::update()
{
    std::chrono::steady_clock::time_point current = std::chrono::steady_clock::now();
    std::chrono::duration<float> span = std::chrono::duration_cast<std::chrono::duration<float>>( current - last );
    //LOG("OLD: " << spanf.count() << " NEW: " << span.count());
    delta_time = span.count();
    last = current;
}

float Timer::get_delta()
{
    return delta_time;
}

float Timer::get_delta_ms()
{
    return delta_time * 1000;
}

} //end namespace Engine
