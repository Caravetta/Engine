#if !defined(UH_EVENT_SYSTEM_H)

#include <string.h>
#include <vector>
#include <unordered_map>
#include "../core_common.h"

namespace core {

    class IEMS;

    typedef CORE_API void (IEMS::*Callback)(void* data);

    class CORE_API IEMS { // Interface Event Management System
    public:
        void create_event_id( std::string event );
        void post_event( std::string event, void* data, size_t data_size );
        void post_event( std::string event );
        void register_event( std::string event, IEMS* obj_ref, Callback func_pointer );
        void unregister_event( std::string event, IEMS* obj_ref, Callback func_pointer );

        static void process_event();
        static void process_all_events();
        static int queued_events();
    };

    struct event_t {
        uint64_t        event_id;
        void*           data;
        size_t          data_size;
        event_t*        next_node;
    };

    struct event_reg_t {
        IEMS*       obj_ref;
        Callback    func_pointer;
        event_reg_t* next_node;
    };

    struct event_reg_list_t {
        event_reg_t* head = NULL;
        event_reg_t* tail = NULL;
    };

    class CEMS { // Core Event Management System
    protected:
        static CEMS* instance;
        uint64_t next_id;
        event_t* queue_head;
        event_t* queue_tail;
        int queue_depth;
        std::unordered_map<std::string, uint64_t> event_map;
        std::vector<event_reg_list_t>* reg_events_list;

        friend IEMS;

    public:
        static CEMS* get_instance();
        void init();
        void create_event_id( std::string event );
        void process_event();
        int event_queue_size();
        void post_event( std::string event, void* data, size_t data_size );
        void register_event( std::string event, IEMS* obj_ref, Callback func_pointer );
        void unregister_event( std::string event, IEMS* obj_ref, Callback func_pointer );
    };

#define WINDOW_SIZE "WINDOW_SIZE" ///?????//////

} //end namespace core

#define UH_EVENT_SYSTEM_H
#endif
