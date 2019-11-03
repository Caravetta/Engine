#include "window.h"

namespace Engine {

Window::Window( int width, int height, std::string title )
{
     __window = platform_window_create(width, height, title);
}

void Window::update( void )
{
     platform_window_update(__window);
}

void Window::swap_buffers( void )
{
     platform_window_swap_buffers(__window);
}

bool Window::is_closed( void )
{
     return platform_window_is_closed(__window);
}

int Window::width( void )
{
     return platform_window_get_width(__window);
}

int Window::height( void )
{
     return platform_window_get_height(__window);
}

void Window::add_key_callback( key_event_cb callback )
{
     platform_window_add_key_event_cb( __window, callback );
}

void Window::add_mouse_position_callback( mouse_position_cb callback )
{
     platform_window_add_mouse_pos_cb( __window, callback );
}

void Window::add_mouse_button_callback( mouse_button_cb callback )
{
     platform_window_add_mouse_button_cb( __window, callback );
}

void Window::add_resize_callback( resize_cb callback )
{
     platform_window_add_resize_cb( __window, callback );
}

} // end namespace Engine

