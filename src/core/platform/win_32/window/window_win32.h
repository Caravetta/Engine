#if !defined(WINDOW_WIN32_H)

#include <string>
#include "../../../core_common.h"

namespace core {

struct platform_window_t* platform_window_create( int width, int height, std::string title );
void platform_window_update( struct platform_window_t* platform_window );
void platform_window_swap_buffers( struct platform_window_t* platform_window );
int platform_window_get_width( struct platform_window_t* platform_window );
int platform_window_get_height( struct platform_window_t* platform_window );

} //end namespace core

#define WINDOW_WIN32_H
#endif
