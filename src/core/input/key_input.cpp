#include "key_input.h"

namespace Engine {

bool key_states[255];

bool is_key_pressed( Key key )
{
     return key_state[key];
}

} // end namespace Engine

