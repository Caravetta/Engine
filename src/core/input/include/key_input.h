#ifndef __KEY_INPUT_H__
#define __KEY_INPUT_H__

#include "core_common.h"
#include "window.h"
#include "key_codes.h"

namespace Engine {

typedef void (*key_event_cb)( Key key, bool is_pressed );

Rc_t init_key_input_system( void );
void add_key_callback( key_event_cb callback );
bool is_key_pressed( Key key );
char key_to_char( Key key );

} // end namespace Engine

#endif
