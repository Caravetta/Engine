#include "window.h"

namespace Engine {
namespace Window {

struct platform_window_t* platform_window;

Rc_t create( uint32_t width, uint32_t height, std::string title )
{
    platform_window = platform_window_create( width, height, title );
    if ( platform_window == NULL ) {
        return ENGINE_ERROR;
    }
    //Input_Manager::get_instance();

    return SUCCESS;
}

void update( void )
{
    platform_window_update(platform_window);
}

void swap_buffers( void )
{
    platform_window_swap_buffers(platform_window);
}

uint32_t get_width( void )
{
    return platform_window_get_width(platform_window);
}

uint32_t get_height( void )
{
    return platform_window_get_height(platform_window);
}

bool is_closed( void )
{
    return platform_window_is_closed(platform_window);
}

Rc_t set_mouse_position( int x, int y )
{
    return platformset_set_mouse_position(platform_window, x, y);
}


} //end namespace Window
} //end namespace Engine
