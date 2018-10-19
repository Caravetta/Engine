#ifndef __SYSTEM_MANAGER_H__
#define __SYSTEM_MANAGER_H__

#include <vector>
#include <unordered_map>
#include "../core_common.h"
#include "system.h"
#include "../entity_system/entity.h"

namespace core {
namespace System_Manager {

CORE_API void init_systems( void );
CORE_API void update_systems( void );
CORE_API void shutdown_systems( void );
CORE_API void register_generic_system( System* system );

std::vector<System*>* get_system_vec( void );

template<typename T>
void System_Manager::register_system( void )
{
    register_generic_system( new T );
}

} //end namespace System_Manager
} //end namespace core

#endif //__SYSTEM_MANAGER_H__
