#ifndef __INPUT_WIN32_H__
#define __INPUT_WIN32_H__

#include "core_common.h"
#include "key_codes.h"

namespace Engine {

typedef void (*platform_key_event_cb)( Key key, bool is_pressed );

Rc_t init_platform_input_system( void );
void platform_key_event( uint32_t key, bool is_pressed );
void platform_add_key_callback( platform_key_event_cb callback );

} // end namespace Engine

#endif //__INPUT_WIN32_H__
