#ifndef __TIMER_H__
#define __TIMER_H__

#include "core_common.h"
#include "platform.h"

namespace Engine {

class Timer {
private:
     platform_timer_t* platform_timer;

public:
     Timer( void );
     ~Timer( void );

     void start( void );
     void stop( void );

     double elapsed_micro_sec( void );
     double elapsed_milli_sec( void );
     double elapsed_sec( void );
};

} // end namespace Engine

#endif //__TIMER_H__
