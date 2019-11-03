#include <sys/time.h>
#include <unistd.h>
#include <new>
#include "timer_linux.h"

namespace Engine {

struct platform_timer_t {
     timeval start_count;
     timeval end_count;
     bool is_running;
};

struct platform_timer_t* platform_timer_create( void )
{
     platform_timer_t* timer = new (std::nothrow) platform_timer_t;

     return timer;
}

void platform_timer_start( struct platform_timer_t* platform_timer )
{
     gettimeofday(&platform_timer->start_count, NULL);
     platform_timer->is_running = true;
}

void platform_timer_stop( struct platform_timer_t* platform_timer )
{
     gettimeofday(&platform_timer->end_count, NULL);
     platform_timer->is_running = false;
}

double platform_timer_elapsed_micro_sec( struct platform_timer_t* platform_timer )
{
     if ( platform_timer->is_running == true ) {
          gettimeofday(&platform_timer->end_count, NULL);
     }

     double start_time = (platform_timer->start_count.tv_sec * 1000000.0) + platform_timer->start_count.tv_usec;
     double end_time = (platform_timer->end_count.tv_sec * 1000000.0) + platform_timer->end_count.tv_usec;

     return end_time - start_time;
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

