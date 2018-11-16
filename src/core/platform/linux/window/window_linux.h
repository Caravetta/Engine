#if !defined(WINDOW_LINUX_H)

#include <string>

namespace core {

struct platform_window_t* platform_window_create( int width, int height, std::string title );
void platform_window_update( struct platform_window_t* platform_window );
void platform_window_swap_buffers( struct platform_window_t* platform_window );
int platform_window_get_width( struct platform_window_t* platform_window );
int platform_window_get_height( struct platform_window_t* platform_window );
bool platform_window_is_closed( struct platform_window_t* platform_window );

} //end namespace core

#define WINDOW_LINUX_H
#endif
