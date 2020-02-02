#ifndef __MOUSE_H__
#define __MOUSE_H__

#include "core_common.h"

namespace Engine {

typedef void (*mouse_move_event_cb)( float mx, float my );

Rc_t init_mouse_system( void );
void add_mouse_move_callback( mouse_move_event_cb callback );
float mouse_x_position( void );
float mouse_y_position( void );

} // end namespace Engine

#endif //__MOUSE_H__
