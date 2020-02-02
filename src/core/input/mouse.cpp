#include "mouse.h"
#include "platform.h"

namespace Engine {

static float mouse_x = 0;
static float mouse_y = 0;

void mouse_move_callback( float mx, float my );

Rc_t init_mouse_system( void )
{
     platform_add_mouse_move_callback(mouse_move_callback);

     return SUCCESS;
}

void add_mouse_move_callback( mouse_move_event_cb callback )
{

}

float mouse_x_position( void )
{
     return mouse_x;
}

float mouse_y_position( void )
{
     return mouse_y;
}

void mouse_move_callback( float mx, float my )
{
     mouse_x = mx;
     mouse_y = my;
}

} // end namespace Engine

