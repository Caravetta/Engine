#ifndef __THREAD_H__
#define __THREAD_H__

#include <functional>
#include "../core_common.h"

#ifdef WINDOWS_PLATFORM
    #include "win_32/thread/thread_win32.h"
#elif LINUX
    #include "linux/thread/thread_linux.h"
#else
    #error "Unsupported Platform"
#endif

namespace core {

typedef platform_lock_t lock_t;

UhRC_t init_lock( lock_t* lock );
void get_lock( lock_t* lock );
void release_lock( lock_t* lock );

typedef struct {
    uint8_t cpu;
    uint32_t thread_id;
    void* thread_handle;
    void (*function)(void* data);
    std::function<void(void* data)> func;
} thread_data_t;

CORE_API void create_thread( thread_data_t* thread_data );
void set_thread_affinity( uint8_t cpu );

} // end namespace core

#endif //__THREAD_H__
