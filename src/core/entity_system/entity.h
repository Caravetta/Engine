#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "../core_common.h"
#include "../handle_system/handle.h"

namespace core {

typedef base_handle_t Entity;

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
