#include <vector>
#include "texture_manager.h"
#include "graphic_utils.h"

namespace Engine {
namespace Texture_Manager {

#define TEXTURE_RESIZE_SIZE 100

typedef struct {
    std::vector<Texture_Handle> texture_handles;
    std::vector<uint32_t> free_handles;
    std::vector<uint32_t> texture_ids;
    uint32_t next_idx;
} texture_manager_t;

texture_manager_t* texture_manager = NULL;

Rc_t init( void ) {
    texture_manager = new (std::nothrow) texture_manager_t;
    if ( texture_manager == NULL ) {
        return MEMORY_ALLOC_FAILED;
    }

    texture_manager->texture_handles.resize(TEXTURE_RESIZE_SIZE);

    for ( uint32_t ii = 0; ii < texture_manager->texture_handles.size(); ++ii ) {
        texture_manager->texture_handles[ii].phase = 0;
        texture_manager->texture_handles[ii].index = ii;
    }

    texture_manager->texture_ids.resize(TEXTURE_RESIZE_SIZE);

    texture_manager->next_idx = 1;

    return SUCCESS;
}

uint32_t get_texture_id( Texture_Handle handle )
{
    // check to make sure the handle is valid
    if ( handle.index < texture_manager->texture_handles.size() && handle.phase == texture_manager->texture_handles[handle.index].phase ) {
        return texture_manager->texture_ids[handle.index];
    }

    return 0;
}

Texture_Handle load_to_graphics_api( Texture* texture )
{
    uint32_t handle_idx = 0;

    if ( texture_manager->free_handles.empty() ) {
        uint32_t current_size = (uint32_t)texture_manager->texture_handles.size();
        if ( texture_manager->next_idx == current_size ) {
            //we need to resize the vector
            texture_manager->texture_handles.resize(current_size + TEXTURE_RESIZE_SIZE);

            for ( uint32_t ii = current_size; ii < texture_manager->texture_handles.size(); ++ii ) {
                texture_manager->texture_handles[ii].phase = 0;
                texture_manager->texture_handles[ii].index = ii;
            }

            texture_manager->texture_ids.resize(current_size + TEXTURE_RESIZE_SIZE);
        }
            handle_idx = texture_manager->next_idx++;


    } else {
        handle_idx = texture_manager->free_handles.back();
        texture_manager->free_handles.pop_back();
    }

    texture_manager->texture_ids[handle_idx] = texture_to_gpu(texture);

    return texture_manager->texture_handles[handle_idx];
}

} // end namespace Texture_Manager
} // end namespace Engine
