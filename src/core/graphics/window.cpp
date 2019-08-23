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

} // end namespace Engine

