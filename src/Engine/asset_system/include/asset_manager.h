#ifndef __ASSET_MANAGER_H__
#define __ASSET_MANAGER_H__

#include "Engine.h"

namespace Engine {
namespace Asset_Manager {

Rc_t init( void );
Rc_t register_asset_generic( const std::string asset_name, const std::string file_path, Asset* asset );
Rc_t get_asset_handle( const std::string asset_name, Asset_Handle* handle );
bool valid_asset_handle( const Asset_Handle handle );
Asset* get_asset_generic( const Asset_Handle handle );

} //end namespace Asset_Manager
} //end namespace Engine

#endif //__ASSET_MANAGER_H__

