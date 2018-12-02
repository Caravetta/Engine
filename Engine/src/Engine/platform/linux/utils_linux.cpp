#include "utils_linux.h"
#include "core_common.h"

namespace Engine {

Rc_t platform_set_thread_affinity( uint64_t logical_cpu )
{
    UNUSED_ARG( logical_cpu );
    return ENGINE_ERROR;
}

uint64_t platform_get_process_affinity_mask()
{
    return 0;
}

void platform_set_process_affinity_mask( uint64_t mask )
{
    UNUSED_ARG( mask );
    return;
}

uint64_t platform_get_system_affinity_mask()
{
    return 0;
}

void* platform_get_current_process()
{
    return NULL;
}

} //end namespace core
