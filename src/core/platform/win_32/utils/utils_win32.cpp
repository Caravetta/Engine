#include <windows.h>
#include "utils_win32.h"

namespace core {

UhRC_t platform_set_thread_affinity( uint64_t logical_cpu )
{
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

} //end namespace core
