#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include "core_common.h"

namespace Engine {

struct System {
public:
     virtual void init( void ) {};
     virtual void update( float time_step ) {};
     virtual void shutdown( void ) {};
};

Rc_t init_system_manager( void );
void register_system( System* system );
template<class T> void register_system( void );

void init_systems( void );
void update_systems( float time_step );
void shutdown_systems( void );

} // end namespace Engine

#include "system.inl"

#endif //__SYSTEM_H__
