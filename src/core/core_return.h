#if !defined(CORE_RETURN_H)

typedef enum {
    SUCCESS               = 0,
    ENGINE_ERROR          = -1000,
    ERROR_INVALID_ENTITY,
    COMPONENT_NOT_SET
} UhRC_t;

#define CORE_RETURN_H
#endif
