#include <pthread.h>
#include "thread_linux.h"

namespace core {

UhRC_t platform_init_lock( platform_lock_t* lock )
{
    return SUCCESS;
}

void platform_get_lock( platform_lock_t* lock )
{

}

void platform_release_lock( platform_lock_t* lock )
{

}

static void* MyThreadFunction( void* arg )
{
    thread_data_window_t* thread_data = (thread_data_window_t*)arg;
#if 0
    TODO HOW?
    SetThreadAffinityMask(GetCurrentThread(), (uint32_t)(1 << thread_data->cpu));
    LOG("CPU " << GetCurrentProcessorNumber());
#endif
    thread_data->function((void*)arg);
    return 0;
}

void platform_create_thread( thread_data_window_t* thread_data )
{
    thread_data->thread_handle = pthread_create(
            &thread_data->thread_id,
            NULL,
            &MyThreadFunction,
            thread_data);

    if ( thread_data->thread_handle != 0 ) {
        LOG_ERROR("Failed to create thread");
    }
}

void platform_set_thread_affinity( uint8_t cpu )
{

}

} // end namespace core
