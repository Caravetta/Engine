#ifndef __THREAD_WIN32_H__
#define __THREAD_WIN32_H__

namespace core {

typedef struct {
    uint8_t cpu;
    uint32_t thread_id;
    void* thread_handle;
    void (*function)(void* data);
} thread_data_window_t;

void platform_create_thread( thread_data_window_t* thread_data );

} // end namespace core

#endif //__THREAD_WIN32_H__
