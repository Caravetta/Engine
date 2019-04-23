#ifndef __UTILS_LINUX_H__
#define __UTILS_LINUX_H__

#include "core_common.h"
#include "return_codes.h"

namespace Engine {

Rc_t platform_set_thread_affinity( uint64_t logical_cpu );

uint64_t platform_get_process_affinity_mask();
void platform_set_process_affinity_mask( uint64_t mask );
uint64_t platform_get_system_affinity_mask();
void* platform_get_current_process();

} //end namespace Engine

#endif //__UTILS_LINUX_H__
