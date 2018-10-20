#include "asset_manager.h"

namespace core {
namespace Asset_Manager {

typedef struct {
    std::vector<Asset*>                         assets;
    std::vector<Asset_Handle>                   asset_handles;
    uint32_t                                    next_handle_idx = 0;
    std::unordered_map<std::string, uint64_t>   asset_handle_map;
    std::unordered_map<uint64_t, uint64_t>      asset_idx_map;
} asset_manager_t;

asset_manager_t asset_manager;

UhRC_t get_asset_handle( std::string asset_name, Asset_Handle* handle )
{
    std::unordered_map<std::string, uint64_t>::const_iterator ele = asset_manager.asset_handle_map.find(asset_name);
    if ( ele == asset_manager.asset_handle_map.end() ) {
        LOG("Not a valid asset name");
        return ENGINE_ERROR;
    }

    handle->id = ele->second;

    return SUCCESS;
}

UhRC_t register_asset_generic( std::string asset_name, std::string file_path, Asset* asset )
{
    uint64_t handle_;

    if ( asset_manager.asset_handles.empty() ) { //there are no released handles
        Asset_Handle handle;
        handle.id = asset_manager.next_handle_idx;
        handle_ = handle.id;
        asset_manager.asset_handle_map.insert({asset_name, handle.id});
        asset_manager.next_handle_idx++;
    } else { //there is a free handle
        Asset_Handle handle = asset_manager.asset_handles[asset_manager.asset_handles.size() - 1];
        handle.id = asset_manager.asset_handles[asset_manager.asset_handles.size() - 1].id;
        handle_ = handle.id;
        asset_manager.asset_handles.pop_back();
        asset_manager.asset_handle_map.insert({asset_name, handle.id});
    }

    asset->load(file_path);
    asset_manager.assets.push_back(asset);

    asset_manager.asset_idx_map.insert({handle_, (asset_manager.assets.size() - 1)});

    return SUCCESS;
}

bool valid_asset_handle( Asset_Handle handle )
{
    std::unordered_map<uint64_t, uint64_t>::const_iterator ele = asset_manager.asset_idx_map.find(handle.id);
    if ( ele == asset_manager.asset_idx_map.end() ) {
        return false;
    }

    return true;
}

Asset* get_asset_generic( Asset_Handle handle )
{
    std::unordered_map<uint64_t, uint64_t>::const_iterator ele = asset_manager.asset_idx_map.find(handle.id);
    if ( ele == asset_manager.asset_idx_map.end() ) {
        return NULL;
    }

    return asset_manager.assets[ele->second];
}

} //end namespace Asset_Manager
} //end namespace core
