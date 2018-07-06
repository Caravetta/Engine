#include "window.h"
#include "../input_system/input_manager.h"

namespace core {

Window::Window( int width, int height, std::string title )
{
    platform_window = platform_window_create( width, height, title );
    Input_Manager::get_instance();
}

void Window::update()
{
    platform_window_update(platform_window);
}

void Window::swap_buffers()
{
    platform_window_swap_buffers(platform_window);
}
int Window::get_width()
{
    return platform_window_get_width(platform_window);
}

int Window::get_height()
{
    return platform_window_get_height(platform_window);
}

bool Window::is_closed()
{
    return platform_window_is_closed(platform_window);
}

} //end namespace core
