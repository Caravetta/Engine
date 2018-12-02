#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <string>
#include "core_common.h"
#include "platform.h"

namespace Engine {
namespace Window {

Rc_t create( uint32_t width, uint32_t height, std::string title );
void update( void );
void swap_buffers( void );
uint32_t get_width( void );
uint32_t get_height( void );
bool is_closed( void );

} //end namespace Window
} //end namesapce Engine

#endif //__WINDOW_H__
