#if !defined(ASSET_MANAGER_H)

#include <vector>
#include <unordered_map>
#include "../core_common.h"
#include "../handle_system/handle.h"
#include "asset.h"

namespace core {

    class CORE_API Asset_Manager {
    private:
        static Asset_Manager* instance;
        std::vector<Asset*> assets;
        std::vector<Handle> asset_handles;
        static uint32_t next_handle_idx;
        std::unordered_map<std::string, uint64_t> asset_handle_map;
        std::unordered_map<uint64_t, uint64_t> asset_idx_map;

    public:
        static Asset_Manager* get_instance();
        template<typename T> UhRC_t register_asset( std::string asset_name, std::string file_path );
        template<typename T> UhRC_t get_asset( Handle asset_handle, T** asset );
        template<typename T> UhRC_t get_asset( std::string asset_name, T** asset );
        UhRC_t get_asset_handle( std::string asset_name, Handle* handle );
    };

template<typename T>
UhRC_t Asset_Manager::register_asset( std::string asset_name, std::string file_path )
{
    uint64_t handle_;
    //TODO: need to check if that name has already been used for another asset

    if ( asset_handles.empty() ) { //there are no released handles
        Handle handle(next_handle_idx);
        handle_ = handle;
        uint64_t a = handle;
        asset_handle_map.insert({asset_name, handle});
        next_handle_idx++;
    } else { //there is a free handle
        Handle handle = asset_handles[asset_handles.size() - 1];
        handle_ = handle;
        asset_handles.pop_back();
        asset_handle_map.insert({asset_name, handle});
    }

    T* temp_asset = new T;
    temp_asset->load(file_path);
    assets.push_back(temp_asset);

    asset_idx_map.insert({handle_, (assets.size() - 1)});

    return SUCCESS;
}

template<typename T>
UhRC_t Asset_Manager::get_asset( Handle asset_handle, T** asset )
{
    std::unordered_map<uint64_t, uint64_t>::const_iterator ele = asset_idx_map.find(asset_handle);
    if ( ele == asset_idx_map.end() ) {
        LOG("Not a valid asset handle"); //TODO: change this to debug logging
        *asset = NULL;
        return ENGINE_ERROR;
    }

    //TODO: add in assert to check that ele < assets.size()

    *asset = (T*)assets.at(ele->second);

    return SUCCESS;
}

template<typename T>
UhRC_t Asset_Manager::get_asset( std::string asset_name, T** asset )
{
    Handle asset_handle;
    UhRC_t rc = get_asset_handle(asset_name, &asset_handle);
    if ( rc == ENGINE_ERROR ) {
        *asset = NULL;
        return ENGINE_ERROR;
    }

    return get_asset<T>(asset_handle, asset);
}

} // end namespace core

#define ASSET_MANAGER_H
#endif
