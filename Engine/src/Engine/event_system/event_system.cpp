#include "event_system.h"

namespace Engine {

void IEMS::create_event_id( std::string event )
{
    CEMS::get_instance()->create_event_id(event);
}

void IEMS::post_event( std::string event, void* data, size_t data_size )
{
    CEMS::get_instance()->post_event(event, data, data_size);
}

void IEMS::post_event( std::string event )
{
    CEMS::get_instance()->post_event(event, NULL, 0);
}

void IEMS::register_event( std::string event, IEMS* obj_ref, Callback func_pointer )
{
    CEMS::get_instance()->register_event(event, obj_ref, func_pointer);
}

void IEMS::unregister_event( std::string event, IEMS* obj_ref, Callback func_pointer )
{
    CEMS::get_instance()->unregister_event(event, obj_ref, func_pointer);
}

void IEMS::process_event()
{
    CEMS::get_instance()->process_event();
}

void IEMS::process_all_events()
{
    while ( CEMS::get_instance()->event_queue_size() > 0 ) {
        process_event();
    }
}

int IEMS::queued_events()
{
    return CEMS::get_instance()->event_queue_size();
}

CEMS* CEMS::instance = NULL;

CEMS* CEMS::get_instance()
{
    if ( instance == NULL ) {
        instance = new CEMS;
        instance->init();
    }
    return instance;
}

void CEMS::init()
{
    queue_head = NULL;
    queue_tail = NULL;
    queue_depth = 0;
    next_id = 0;
    event_map.clear();
    reg_events_list = new std::vector<event_reg_list_t>;
}

void CEMS::create_event_id( std::string event )
{
    std::unordered_map<std::string, uint64_t>::const_iterator ele = event_map.find(event);

    if ( ele == event_map.end() ) {
        event_map.insert({ event, next_id });
        if ( reg_events_list->capacity() < next_id + 5 ) {
            reg_events_list->reserve(next_id + 50);
        }
        event_reg_list_t temp;
        temp.head = NULL;
        temp.tail = NULL;
        reg_events_list->push_back(temp);
        next_id += 1;
    } else {
        LOG("Event: " << ele->first << " existed with id: " << ele->second);
    }
}

int CEMS::event_queue_size()
{
    return queue_depth;
}

void CEMS::process_event()
{
    if ( queue_depth == 0 ) {
        return;
    }

    event_t* current_event = queue_head;
    queue_head = queue_head->next_node;
    queue_depth -= 1;

    if ( queue_head == NULL ) {
        queue_tail = NULL;
    }

    event_reg_t* current_handle = reg_events_list->at(current_event->event_id).head;

    while( current_handle != NULL ) {
        (current_handle->obj_ref->*(current_handle->func_pointer))(current_event->data);
        current_handle = current_handle->next_node;
    }
}

void CEMS::post_event( std::string event, void* data, size_t data_size )
{
    std::unordered_map<std::string, uint64_t>::const_iterator ele = event_map.find(event);
    if (ele == event_map.end()) {
        //LOG_ERROR("Event " << event << " does not exist");
        return;
    }
#if 0
    if (reg_events_list->at(ele->second).head == NULL) {
        UH_LOG("No one is subed");
        return;
    }
#endif
    event_t* new_event = new event_t;

    new_event->event_id = ele->second;
    new_event->next_node = NULL;

    if ( data && data_size ) {
        new_event->data = new char [data_size];
        new_event->data_size = data_size;
        memcpy(new_event->data, data, data_size);
    } else {
        new_event->data = NULL;
        new_event->data_size = 0;
    }

    if ( queue_head == NULL && queue_tail == NULL ) {
        queue_head = new_event;
        queue_tail = new_event;
    } else {
        queue_tail->next_node = new_event;
        queue_tail = new_event;
    }

    queue_depth += 1;
}

void CEMS::register_event( std::string event, IEMS* obj_ref, Callback func_pointer )
{
    std::unordered_map<std::string, uint64_t>::const_iterator ele = event_map.find(event);
    if ( ele == event_map.end() ) {
        LOG_ERROR("Event " << event << " does not exist");
        return;
    }

    event_reg_t* new_node = new event_reg_t;
    new_node->obj_ref = obj_ref;
    new_node->func_pointer = func_pointer;
    new_node->next_node = NULL;

    if ( reg_events_list->at(ele->second).head == NULL && reg_events_list->at(ele->second).tail == NULL ) {
        reg_events_list->at(ele->second).head = new_node;
        reg_events_list->at(ele->second).tail = new_node;
    } else {
        reg_events_list->at(ele->second).tail->next_node = new_node;
        reg_events_list->at(ele->second).tail = new_node;
    }
}

void CEMS::unregister_event( std::string event, IEMS* obj_ref, Callback func_pointer )
{
    //TODO: come up with a better way to do this
}

} //end namespace core
