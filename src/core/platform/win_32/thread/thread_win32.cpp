#include "thread_win32.h"

namespace core {

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
    }
}

} // end namespace core
