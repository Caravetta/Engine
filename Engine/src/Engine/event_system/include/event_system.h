#ifndef __EVENT_SYSTEM_H__
#define __EVENT_SYSTEM_H__

#include <string.h>
#include <vector>
#include <unordered_map>
#include "core_common.h"

namespace Engine {
namespace Event_Manager {

Rc_t init( void );
Rc_t create_event_id( std::string event_name );
Rc_t process_event( void );
Rc_t subscribe_to_event( std::string event_name, void (*callback)(void*, size_t));
Rc_t unsubscribe_to_event();
Rc_t broadcast_event( std::string event_name, void* data, size_t data_size );

} // end namespace Event_Manager
} // end namespace Engine

#endif //__EVENT_SYSTEM_H__
