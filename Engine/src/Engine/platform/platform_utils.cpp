#include <thread>
#include "platform_utils.h"
#include "platform.h"

namespace Engine {

uint32_t get_logical_core_count()
{
    return (uint32_t)std::thread::hardware_concurrency();
}

uint64_t get_process_affinity_mask()
{
    return platform_get_process_affinity_mask();
}

void set_process_affinity_mask( uint64_t mask )
{
    platform_set_process_affinity_mask(mask);
}

uint64_t get_system_affinity_mask()
{
    return platform_get_system_affinity_mask();
}

void* get_current_process()
{
    return platform_get_current_process();
}

} // end namespace Engine
