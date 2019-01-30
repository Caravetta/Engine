#include <cstring>
#include "input_manager.h"
#include "event_system.h"

namespace Engine {
namespace Input_Manager {

#define MOUSE_POS_TO_OPENGL( mouse, offset, window ) ((mouse - offset - (window/2)) / (window/2))

typedef struct {
    bool key_pressed_state[MAX_SCANCODE_COUNT];
} input_manager_t;

input_manager_t input_manager;

Rc_t init( void )
{
    memset(input_manager.key_pressed_state, 0, MAX_SCANCODE_COUNT);
    init_scancode_to_key_map();

    return SUCCESS;
}

bool is_key_pressed( key_t key )
{
    return input_manager.key_pressed_state[key];
}

void process_key_down( key_t key )
{
    input_manager.key_pressed_state[key] = true;
}

void process_key_up( key_t key )
{
    input_manager.key_pressed_state[key] = false;
}

void process_mouse_move( uint64_t x_pos, uint64_t y_pos )
{
    UNUSED_ARG(x_pos);
    UNUSED_ARG(y_pos);

}

} // end namespace Input_Manager
} // end namespace Engine
