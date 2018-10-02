#ifndef __CORE_RETURN_H__
#define __CORE_RETURN_H__

typedef enum {
    SUCCESS               = 0,
    ENGINE_ERROR          = -1000,
    ERROR_INVALID_ENTITY,
    COMPONENT_NOT_SET,
    ARCHETYPE_EXISTS,
    ARCHETYPE_DOES_NOT_EXIST,
    MEMORY_ALLOC_FAILED,
    ENTITY_NOT_VALID
} UhRC_t;

#endif //__CORE_RETURN_H__
