#include "timer.h"

namespace Engine {

Timer::Timer( void )
{
     platform_timer = platform_timer_create();
}

Timer::~Timer( void )
{
     if ( platform_timer != NULL ) {
          free(platform_timer);
     }
}

void Timer::start( void )
{
     platform_timer_start(platform_timer);
}

void Timer::stop( void )
{
     platform_timer_stop(platform_timer);
}

double Timer::elapsed_micro_sec( void )
{
     return platform_timer_elapsed_micro_sec(platform_timer);
}

double Timer::elapsed_milli_sec( void )
{
     return platform_timer_elapsed_milli_sec(platform_timer);
}

double Timer::elapsed_sec( void )
{
     return platform_timer_elapsed_sec(platform_timer);
}

}; // end namespace Engine

