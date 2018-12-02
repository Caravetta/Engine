#include "thread_win32.h"

namespace Engine {

Rc_t platform_init_lock( platform_lock_t* lock )
{
    if ( !InitializeCriticalSectionAndSpinCount(lock, 0x00000400) ) {
        return ENGINE_ERROR;
    }

    return SUCCESS;
}

void platform_get_lock( platform_lock_t* lock )
{
    EnterCriticalSection(lock);
}

void platform_release_lock( platform_lock_t* lock )
{
    LeaveCriticalSection(lock);
}

DWORD WINAPI MyThreadFunction( LPVOID lpParam )
{
    thread_data_window_t* thread_data = (thread_data_window_t*)lpParam;
    SetThreadAffinityMask(GetCurrentThread(), (uint32_t)(1 << thread_data->cpu));
    //LOG("CPU " << GetCurrentProcessorNumber());
    thread_data->function((void*)lpParam);
    return 0;
}

void platform_create_thread( thread_data_window_t* thread_data )
{
    thread_data->thread_handle = CreateThread(
            NULL,                                   // default security attributes
            0,                                      // use default stack size
            MyThreadFunction,                       // thread function name
            thread_data,                            // argument to thread function
            0,                                      // use default creation flags
            (DWORD*)&thread_data->thread_id);

    if ( thread_data->thread_handle == NULL ) {
        LOG_ERROR("Failed to create thread");
    } else {
        SetThreadPriority( thread_data->thread_handle, THREAD_PRIORITY_ABOVE_NORMAL );
    }
}

void platform_set_thread_affinity( uint8_t cpu )
{
    SetThreadAffinityMask(GetCurrentThread(), (uint32_t)(1 << cpu));
}

} // end namespace Engine
