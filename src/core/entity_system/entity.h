#if !defined(ENTITY_H)

#include "../core_common.h"
#include "../handle_system/handle.h"

namespace core {

typedef base_handle_t Entity;
#if 0
    struct Entity {
        Handle id;

        Entity() {
            id = 0;
        };
    };
#endif
} // end namespace core

#define ENTITY_H
#endif
