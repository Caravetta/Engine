#ifndef __TIMER_WIN32_H__
#define __TIMER_WIN32_H__

#include "core_common.h"

namespace Engine {

struct platform_timer_t* platform_timer_create( void );

void platform_timer_start( struct platform_timer_t* platform_timer );
void platform_timer_stop( struct platform_timer_t* platform_timer );

double platform_timer_elapsed_micro_sec( struct platform_timer_t* platform_timer );
double platform_timer_elapsed_milli_sec( struct platform_timer_t* platform_timer );
double platform_timer_elapsed_sec( struct platform_timer_t* platform_timer );

} // end namespace Engine

#endif //__TIMER_WIN32_H__
