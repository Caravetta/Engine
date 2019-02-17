#include <vector>
#include <unordered_map>
#include "asset_manager.h"
#include "core_common.h"

namespace Engine {
namespace Asset_Manager {

typedef struct {
    std::vector<Asset*>                     assets;
    std::vector<Asset_Handle>               asset_handles;
    u32                                     next_handle_idx;
    std::unordered_map<std::string, u64>    asset_handle_map;
    std::unordered_map<u64, u64>            asset_idx_map;
} asset_manager_t;

asset_manager_t* asset_manager = NULL;

Rc_t init( void )
{
    asset_manager = new (std::nothrow) asset_manager_t;
    if ( asset_manager == NULL ) {
        return MEMORY_ALLOC_FAILED;
    }

    asset_manager->next_handle_idx = 0;

    return SUCCESS;
}

Rc_t get_asset_handle( const std::string asset_name, Asset_Handle* handle )
{
    UNORDERED_MAP_ITERATOR(std::string, u64) iter = asset_manager->asset_handle_map.find(asset_name);
    if ( iter == asset_manager->asset_handle_map.end() ) {
        LOG_ERROR("Not a valid asset name: " << asset_name);
        return INVALID_ASSET_NAME;
    }

    handle->id = iter->second;

    return SUCCESS;
}

Rc_t register_asset_generic( const std::string asset_name, const std::string file_path, Asset* asset )
{
    u64 handle;
    UNORDERED_MAP_ITERATOR(std::string, u64) iter = asset_manager->asset_handle_map.find(asset_name);
    if ( iter == asset_manager->asset_handle_map.end() ) {
        if ( asset_manager->asset_handles.empty() ) {
            // there are no released handles
            handle = asset_manager->next_handle_idx;
            asset_manager->asset_handle_map.insert({asset_name, handle});
            asset_manager->next_handle_idx += 1;
        } else {
            // there is a free handle
            Asset_Handle handle_ = asset_manager->asset_handles[asset_manager->asset_handles.size() - 1];
            handle_.id = asset_manager->asset_handles[asset_manager->asset_handles.size() - 1].id;
            handle = handle_.id;
            asset_manager->asset_handles.pop_back();
            asset_manager->asset_handle_map.insert({asset_name, handle_.id});
        }

        asset->load(file_path);
        asset_manager->assets.push_back(asset);

        asset_manager->asset_idx_map.insert({handle, (asset_manager->assets.size() - 1)});

        return SUCCESS;
    }

    return ASSET_NAME_ALREADY_USED;
}

bool valid_asset_handle( const Asset_Handle handle )
{
    UNORDERED_MAP_ITERATOR(u64, u64) iter = asset_manager->asset_idx_map.find(handle.id);
    if ( iter == asset_manager->asset_idx_map.end() ) {
        return false;
    }

    return true;
}

Asset* get_asset_generic( const Asset_Handle handle )
{
    UNORDERED_MAP_ITERATOR(u64, u64) iter = asset_manager->asset_idx_map.find(handle.id);
    if ( iter == asset_manager->asset_idx_map.end() ) {
        return NULL;
    }

    return asset_manager->assets[iter->second];
}

} //end namespace Asset_Manager
} //end namespace Engine
