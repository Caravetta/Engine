#include "assert.h"
namespace core {

UhRC_t platform_set_thread_affinity( uint64_t logical_cpu )
{
    assert(0);
    return ENGINE_ERROR;
}

uint64_t platform_get_process_affinity_mask()
{
    assert(0);
    return 0;
}

void platform_set_process_affinity_mask( uint64_t mask )
{
    (void)mask;
    assert(0);
}

uint64_t platform_get_system_affinity_mask()
{
    assert(0);
    return 0;
}

void* platform_get_current_process()
{
    assert(0);
    return NULL;
}

} //end namespace core
