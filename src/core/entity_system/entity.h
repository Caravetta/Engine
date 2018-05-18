#if !defined(ENTITY_H)

#include "../core_common.h"
#include "../handle_system/handle.h"

namespace core {

    struct Entity {
        Handle id;

        Entity() {
            id = 0;
        };
    };

} // end namespace core

#define ENTITY_H
#endif
