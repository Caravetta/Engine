#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <string>
#include "core_common.h"
#include "platform.h"

namespace Engine {

class Window {
private:
     platform_window_t* __window;

public:
     Window( int width, int height, std::string title );
     void update( void );
     void swap_buffers( void );
     bool is_closed( void );
     int width( void );
     int height( void );
     //void add_key_callback( key_event_cb callback );
     void add_mouse_position_callback( mouse_position_cb callback );
     void add_mouse_button_callback( mouse_button_cb callback );
     void add_resize_callback( resize_cb callback );
};

} // end namespace Engine

#endif //__WINDOW_H__
