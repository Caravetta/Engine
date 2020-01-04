#ifndef __WINDOW_LINUX_H__
#define __WINDOW_LINUX_H__

#include <string>
#include "core_common.h"

namespace Engine {

struct platform_window_t* platform_window_create( int width, int height, std::string title );
void platform_window_update( struct platform_window_t* platform_window );
void platform_window_swap_buffers( struct platform_window_t* platform_window );
bool platform_window_is_closed( struct platform_window_t* platform_window );
int platform_window_get_width( struct platform_window_t* platform_window );
int platform_window_get_height( struct platform_window_t* platform_window );
//int platform_window_add_key_event_cb( struct platform_window_t* platform_window, key_event_cb callback );
int platform_window_add_mouse_pos_cb( struct platform_window_t* platform_window, mouse_position_cb callback );
int platform_window_add_mouse_button_cb( struct platform_window_t* platform_window, mouse_button_cb callback );
int platform_window_add_resize_cb( struct platform_window_t* platform_window, resize_cb callback );

} // end namespace Engine

#endif //__WINDOW_LINUX_H__

