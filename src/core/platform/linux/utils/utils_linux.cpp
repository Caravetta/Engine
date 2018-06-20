#include "utils_win32.h"

namespace core {

UhRC_t platform_set_thread_affinity( uint64_t logical_cpu )
{
    return ENGINE_ERROR;
}

uint64_t platform_get_process_affinity_mask()
{
    asset(!"Not implemented");
    return 0;
}

void platform_set_process_affinity_mask( uint64_t mask )
{
    (void)mask;
    asset(!"Not implemented");
}

uint64_t platform_get_system_affinity_mask()
{
    asset(!"Not implemented");
    return 0;
}

void* platform_get_current_process()
{
    asset(!"Not implemented");
    return NULL;
}

} //end namespace core
