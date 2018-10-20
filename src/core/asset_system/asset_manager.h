#ifndef __ASSET_MANAGER_H__
#define __ASSET_MANAGER_H__

#include <vector>
#include <unordered_map>

#include "../core_common.h"
#include "../handle_system/handle.h"
#include "asset.h"

namespace core {
namespace Asset_Manager {

CORE_API UhRC_t register_asset_generic( std::string asset_name, std::string file_path, Asset* asset );
CORE_API UhRC_t get_asset_handle( std::string asset_name, Asset_Handle* handle );
CORE_API bool valid_asset_handle( Asset_Handle handle );
CORE_API Asset* get_asset_generic( Asset_Handle handle );

template<typename T>
UhRC_t Asset_Manager::register_asset( std::string asset_name, std::string file_path )
{
    //TODO: need to check if that name has already been used for another asset
    return register_asset_generic(asset_name, file_path, new T);
}

template<typename T>
UhRC_t Asset_Manager::get_asset_with_handle( Asset_Handle asset_handle, T** asset )
{
    *asset = (T*)get_asset_generic(asset_handle);

    if ( *asset == NULL ) {
        return ENGINE_ERROR;
    }

    return SUCCESS;
}

template<typename T>
UhRC_t Asset_Manager::get_asset( std::string asset_name, T** asset )
{
    Asset_Handle asset_handle;
    UhRC_t rc = get_asset_handle(asset_name, &asset_handle);
    if ( rc == ENGINE_ERROR ) {
        *asset = NULL;
        return ENGINE_ERROR;
    }

    return get_asset_with_handle<T>(asset_handle, asset);
}

} //end namespace Asset_Manager
} //end namespace core

#endif //__ASSET_MANAGER_H__

