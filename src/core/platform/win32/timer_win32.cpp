#include <new>
#include "timer_win32.h"

namespace Engine {

struct platform_timer_t {
     int place_holder;
};

struct platform_timer_t* platform_timer_create( void )
{
     platform_timer_t* timer = new (std::nothrow) platform_timer_t;

     return timer;
}

void platform_timer_start( struct platform_timer_t* platform_timer )
{
}

void platform_timer_stop( struct platform_timer_t* platform_timer )
{
}

double platform_timer_elapsed_micro_sec( struct platform_timer_t* platform_timer )
{
     return 0;
}

double platform_timer_elapsed_milli_sec( struct platform_timer_t* platform_timer )
{
     return platform_timer_elapsed_micro_sec(platform_timer) * 0.001;
}

double platform_timer_elapsed_sec( struct platform_timer_t* platform_timer )
{
     return platform_timer_elapsed_micro_sec(platform_timer) * 0.000001;
}

} // end namespace Engine

