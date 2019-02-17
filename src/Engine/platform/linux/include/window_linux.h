#if !defined(WINDOW_LINUX_H)

#include <string>
#include "Engine_Types.h"

namespace Engine {

struct platform_window_t* platform_window_create( int width, int height, std::string title );
void platform_window_update( struct platform_window_t* platform_window );
void platform_window_swap_buffers( struct platform_window_t* platform_window );
int platform_window_get_width( struct platform_window_t* platform_window );
int platform_window_get_height( struct platform_window_t* platform_window );
bool platform_window_is_closed( struct platform_window_t* platform_window );
Rc_t platformset_set_mouse_position( struct platform_window_t* platform_window, int x, int y );

} //end namespace Engine

#define WINDOW_LINUX_H
#endif
