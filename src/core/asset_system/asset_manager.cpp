#include "asset_manager.h"

namespace core {

Asset_Manager* Asset_Manager::instance = NULL;
uint32_t Asset_Manager::next_handle_idx = 0;

Asset_Manager* Asset_Manager::get_instance()
{
    if ( instance == NULL ) {
        LOG("Initializing Asset_Manager");
        instance = new Asset_Manager;
    }

    return instance;
}

UhRC_t Asset_Manager::get_asset_handle( std::string asset_name, Handle* handle )
{
    Handle tmp_handle;

    std::unordered_map<std::string, uint64_t>::const_iterator ele = asset_handle_map.find(asset_name);
    if ( ele == asset_handle_map.end() ) {
        LOG("Not a valid asset name");
        return ENGINE_ERROR;
    }

    tmp_handle = ele->second;

    *handle = tmp_handle;

    return SUCCESS;
}

} // end namespace core
