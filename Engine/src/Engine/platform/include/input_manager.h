#ifndef __INPUT_MANAGER_H__
#define __INPUT_MANAGER_H__

#include <string>
#include <unordered_map>
#include "core_common.h"
#include "event_system.h"
#include "Engine_Types.h"
#include "platform.h"

namespace Engine {
namespace Input_Manager {

Rc_t init( void );
bool is_key_pressed( key_t key );

void process_key_down( key_t key );
void process_key_up( key_t key );
void process_mouse_move( uint64_t x_pos, uint64_t y_pos );

} // end namespace Input_Manager
} // end namespace Engine

#endif //__INPUT_MANAGER_H__
