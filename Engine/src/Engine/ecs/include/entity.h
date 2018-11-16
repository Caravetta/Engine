#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "core_common.h"
//#include "handle.h"

namespace Engine {

//typedef base_handle_t Entity;

typedef struct {
    union {
        struct {
            uint64_t index  : 32;
            uint64_t phase  : 31;
            uint64_t active : 1;
        };
        uint64_t id;
    };
} Entity;

typedef struct {
    union {
        struct {
            uint64_t archetype : 32;
            uint64_t index     : 32;
        };
        uint64_t id;
    };
} internal_entity_id;

} // end namespace core

#endif //__ENTITY_H__
