#ifndef __THREAD_LINUX_H__
#define __THREAD_LINUX_H__

namespace core {

typedef struct {
    uint8_t cpu;
    uint32_t thread_id;
    void* thread_handle;
    void (*function)(void* data);
} thread_data_window_t;

typedef int platform_lock_t;

UhRC_t platform_init_lock( platform_lock_t* lock );
void platform_get_lock( platform_lock_t* lock );
void platform_release_lock( platform_lock_t* lock );

void platform_create_thread( thread_data_window_t* thread_data );
void platform_set_thread_affinity( uint8_t cpu );

} // end namespace core

#endif //__THREAD_LINUX_H__
