#ifndef __PLATFORM_UTILS_H__
#define __PLATFORM_UTILS_H__

#include "core_common.h"

namespace Engine {

uint32_t get_logical_core_count();

uint64_t get_process_affinity_mask();
void set_process_affinity_mask( uint64_t mask );

uint64_t get_system_affinity_mask();

void* get_current_process();

} // end namespace Engine

#endif //__PLATFORM_UTILS_H__
