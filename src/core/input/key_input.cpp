#include "key_input.h"

namespace Engine {

void key_event_callback( char key, bool is_pressed );

bool key_states[KEY_MAX_COUNT] = {false};

Rc_t init_key_input_system( Window& window )
{
     window.add_key_callback(key_event_callback);
     return SUCCESS;
}

bool is_key_pressed( Key key )
{
     return key_state[key];
}

void key_event_callback( char key, bool is_pressed )
{
     key_states[key] = is_pressed;
}

} // end namespace Engine

