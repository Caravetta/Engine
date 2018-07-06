#if !defined(THREAD_LINUX_H)

namespace core {

typedef struct {
    uint8_t cpu;
    uint32_t thread_id;
    void* thread_handle;
    void (*function)(void* data);
} thread_data_window_t;

void platform_create_thread( thread_data_window_t* thread_data );

} // end namespace core

#define THREAD_LINUX_H
#endif
