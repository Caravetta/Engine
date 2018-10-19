#ifndef __THREAD_H__
#define __THREAD_H__

#include <functional>
#include "../core_common.h"

namespace core {

typedef struct {
    uint8_t cpu;
    uint32_t thread_id;
    void* thread_handle;
    void (*function)(void* data);
    std::function<void(void* data)> func;
} thread_data_t;

CORE_API void create_thread( thread_data_t* thread_data );

} // end namespace core

#endif //__THREAD_H__
