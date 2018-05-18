#if !defined(THREAD_H)

#include "../core_common.h"

namespace core {

typedef struct {
    uint8_t cpu;
    uint32_t thread_id;
    void* thread_handle;
    void (*function)(void* data);
} thread_data_t;

CORE_API void create_thread( thread_data_t* thread_data );

} // end namespace core

#define THREAD_H
#endif
