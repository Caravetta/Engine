#include <Engine.h>
#include "input_tracker.h"

namespace Input_Tracker {

#define UNUSED_ARG( x ) ((void)(x))

typedef struct {
    std::vector<bool> key_state;
} input_tracker_t;

input_tracker_t input_tracker;


void w_pressed( void* data, size_t data_size )
{
    UNUSED_ARG( data );
    UNUSED_ARG( data_size );
    input_tracker.key_state[W_KEY_STATE] = true;
}

void a_pressed( void* data, size_t data_size )
{
    UNUSED_ARG( data );
    UNUSED_ARG( data_size );
    input_tracker.key_state[A_KEY_STATE] = true;
}

void s_pressed( void* data, size_t data_size )
{
    UNUSED_ARG( data );
    UNUSED_ARG( data_size );
    input_tracker.key_state[S_KEY_STATE] = true;
}

void d_pressed( void* data, size_t data_size )
{
    UNUSED_ARG( data );
    UNUSED_ARG( data_size );
    input_tracker.key_state[D_KEY_STATE] = true;
}

void w_released( void* data, size_t data_size )
{
    UNUSED_ARG( data );
    UNUSED_ARG( data_size );
    input_tracker.key_state[W_KEY_STATE] = false;
}

void a_released( void* data, size_t data_size )
{
    UNUSED_ARG( data );
    UNUSED_ARG( data_size );
    input_tracker.key_state[A_KEY_STATE] = false;
}

void s_released( void* data, size_t data_size )
{
    UNUSED_ARG( data );
    UNUSED_ARG( data_size );
    input_tracker.key_state[S_KEY_STATE] = false;
}

void d_released( void* data, size_t data_size )
{
    UNUSED_ARG( data );
    UNUSED_ARG( data_size );
    input_tracker.key_state[D_KEY_STATE] = false;
}

void init()
{
    input_tracker.key_state.resize(KEY_STATE_COUNT);
    for ( uint32_t ii = 0; ii < KEY_STATE_COUNT; ++ii ) {
        input_tracker.key_state[ii] = false;
    }

    Engine::subscribe_to_event("KEY_W_PRESSED", &w_pressed);
    Engine::subscribe_to_event("KEY_A_PRESSED", &a_pressed);
    Engine::subscribe_to_event("KEY_S_PRESSED", &s_pressed);
    Engine::subscribe_to_event("KEY_D_PRESSED", &d_pressed);

    Engine::subscribe_to_event("KEY_W_RELEASED", &w_released);
    Engine::subscribe_to_event("KEY_A_RELEASED", &a_released);
    Engine::subscribe_to_event("KEY_S_RELEASED", &s_released);
    Engine::subscribe_to_event("KEY_D_RELEASED", &d_released);
}

bool is_key_pressed( tracked_keys_t key )
{
    return input_tracker.key_state[key];
}

} // end namespace Input_Tracker

