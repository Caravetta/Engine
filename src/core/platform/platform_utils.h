#ifndef __PLATFORM_UTILS_H__
#define __PLATFORM_UTILS_H__

#include "../core_common.h"

namespace core {

CORE_API uint32_t get_logical_core_count();

CORE_API uint64_t get_process_affinity_mask();
CORE_API void set_process_affinity_mask( uint64_t mask );

CORE_API uint64_t get_system_affinity_mask();

CORE_API void* get_current_process();

} // end namespace core

#endif //__PLATFORM_UTILS_H__
