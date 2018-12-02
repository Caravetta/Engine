#ifndef __ASSET_MANAGER_H__
#define __ASSET_MANAGER_H__

#include <vector>
#include <unordered_map>
#include "core_common.h"
#include "Engine.h"

namespace Engine {
namespace Asset_Manager {

Rc_t register_asset_generic( std::string asset_name, std::string file_path, Asset* asset );
Rc_t get_asset_handle( std::string asset_name, Asset_Handle* handle );
bool valid_asset_handle( Asset_Handle handle );
Asset* get_asset_generic( Asset_Handle handle );

} //end namespace Asset_Manager
} //end namespace Engine

#endif //__ASSET_MANAGER_H__

