#if !defined(CORE_RETURN_H)

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

#define CORE_RETURN_H
#endif
