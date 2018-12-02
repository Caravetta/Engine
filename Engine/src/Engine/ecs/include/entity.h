#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "core_common.h"

namespace Engine {

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
