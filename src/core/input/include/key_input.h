#ifndef __KEY_INPUT_H__
#define __KEY_INPUT_H__

#include "core_common.h"
#include "platform.h"

namespace Engine {

//typedef void (*key_event_cb)( char key, bool is_pressed );

enum Key {
     W_KEY = PLATFORM_W_KEY,
     A_KEY = PLATFORM_A_KEY,
     S_KEY = PLATFORM_S_KEY,
     D_KEY = PLATFORM_D_KEY,
};

bool is_key_pressed( Key key );

} // end namespace Engine

#endif
