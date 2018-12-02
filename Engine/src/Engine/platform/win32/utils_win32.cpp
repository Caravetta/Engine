#include <windows.h>
#include "utils_win32.h"
#include "core_common.h"

namespace Engine {

Rc_t platform_set_thread_affinity( uint64_t logical_cpu )
{
    UNUSED_ARG( logical_cpu );
    return ENGINE_ERROR;
}

uint64_t platform_get_process_affinity_mask()
{
    HANDLE process = GetCurrentProcess();
    uint64_t processAffinityMask = NULL;
    uint64_t systemAffinityMask = NULL;
    GetProcessAffinityMask(process, &processAffinityMask, &systemAffinityMask);
    return processAffinityMask;
}

void platform_set_process_affinity_mask( uint64_t mask )
{
    HANDLE process = GetCurrentProcess();
    BOOL rc = SetProcessAffinityMask(process, mask);
    UNUSED_ARG( rc );
}

uint64_t platform_get_system_affinity_mask()
{
    HANDLE process = GetCurrentProcess();
    uint64_t processAffinityMask = NULL;
    uint64_t systemAffinityMask = NULL;
    GetProcessAffinityMask(process, &processAffinityMask, &systemAffinityMask);
    return systemAffinityMask;
}

void* platform_get_current_process()
{
    return GetCurrentProcess();
}

} //end namespace Engine
