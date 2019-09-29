#include "key_input.h"

namespace Engine {

bool is_key_pressed( Key key )
{
     return key_state[key];
}

} // end namespace Engine

