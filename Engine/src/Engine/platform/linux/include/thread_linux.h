#ifndef __THREAD_LINUX_H__
#define __THREAD_LINUX_H__

#include "core_common.h"

namespace Engine {

typedef struct {
    uint8_t cpu;
    uint32_t thread_id;
    pthread_t thread_handle;
    void ( *function )( void *data );
} thread_data_window_t;

typedef pthread_spinlock_t platform_lock_t;

Rc_t platform_init_lock( platform_lock_t *lock );
void platform_get_lock( platform_lock_t *lock );
void platform_release_lock( platform_lock_t *lock );

void platform_create_thread( thread_data_window_t *thread_data );
void platform_set_thread_affinity( uint8_t cpu );

} // end namespace Engine

#endif //__THREAD_LINUX_H__
