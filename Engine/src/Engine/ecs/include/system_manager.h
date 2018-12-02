#ifndef __SYSTEM_MANAGER_H__
#define __SYSTEM_MANAGER_H__

#include <vector>
#include <unordered_map>
#include "core_common.h"
#include "system.h"
#include "entity.h"

namespace Engine {
namespace System_Manager {

void init_systems( void );
void update_systems( void );
void shutdown_systems( void );

std::vector<System*>* get_system_vec( void );

} //end namespace System_Manager
} //end namespace Engine

#endif //__SYSTEM_MANAGER_H__
