#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "core_common.h"

namespace Engine {

typedef struct {
    union {
        struct {
            u64 archetype : 32;
            u64 index     : 32;
        };
        u64 id;
    };
} internal_entity_id;

} // end namespace core

#endif //__ENTITY_H__
