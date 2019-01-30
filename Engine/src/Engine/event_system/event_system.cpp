#include <queue>
#include "event_system.h"
#include "Engine.h"

namespace Engine {
namespace Event_Manager {

#define EVENT_RESIZE_SIZE 10

typedef std::vector<void (*)(void *, size_t)> call_back_funcs;

typedef struct {
    std::string event_name;
    void* data;
    size_t data_size;
} event_node;

typedef struct {
    uint64_t next_event_id;
    std::vector<call_back_funcs> events;
    std::unordered_map<std::string, uint64_t> event_map;
    std::queue<event_node> event_queue;
} event_manager_t;

event_manager_t event_manager;

Rc_t init( void )
{
    event_manager.next_event_id = 0;
    event_manager.events.resize(EVENT_RESIZE_SIZE);
    return SUCCESS;
}

Rc_t create_event_id( std::string event_name )
{
    std::unordered_map<std::string, uint64_t>::const_iterator ele = event_manager.event_map.find(event_name);
    if (ele == event_manager.event_map.end()) {
        if ( event_manager.next_event_id == event_manager.events.size() ) {
            event_manager.events.resize(EVENT_RESIZE_SIZE + event_manager.events.size());
        }
        event_manager.event_map.insert({ event_name, event_manager.next_event_id++ });
    }
    return SUCCESS;
}

Rc_t process_event( void )
{
    if ( !event_manager.event_queue.empty() ) {
        // get the first event off the queue
        event_node current_event = event_manager.event_queue.front();
        event_manager.event_queue.pop();

        // walk down all the subs and call their callback functions
        std::unordered_map<std::string, uint64_t>::const_iterator ele = event_manager.event_map.find(current_event.event_name);
        for ( uint64_t ii = 0; ii <  event_manager.events[ele->second].size(); ++ii ) {
            event_manager.events[ele->second][ii](NULL, 0);
        }
    }

    return SUCCESS;
}

Rc_t subscribe_to_event( std::string event_name, void (*callback)(void*, size_t) )
{
    std::unordered_map<std::string, uint64_t>::const_iterator ele = event_manager.event_map.find(event_name);
    if ( ele != event_manager.event_map.end() ) {
        event_manager.events[ele->second].push_back(callback);

        return SUCCESS;
    }
    return INVALID_EVENT_NAME;
}

Rc_t unsubscribe_to_event()
{
    return SUCCESS;
}

Rc_t broadcast_event( std::string event_name, void* data, size_t data_size )
{
    std::unordered_map<std::string, uint64_t>::const_iterator ele = event_manager.event_map.find(event_name);
    if ( ele != event_manager.event_map.end() ) {
        event_node new_node;
        new_node.event_name = event_name;
        new_node.data = data;
        new_node.data_size = data_size;

        event_manager.event_queue.push(new_node);

        return SUCCESS;
    }

    return INVALID_EVENT_NAME;
}

} // end namespace Event_Manager
} // end namespace Engine
