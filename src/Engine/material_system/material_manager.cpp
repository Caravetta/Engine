#include "material_manager.h"
#include "core_common.h"

namespace Engine {
namespace Material_Manager {

#define MATERIAL_RESIZE_SIZE 100
#define RESERVED_MATERIAL_HANDLE 0

typedef struct {
    std::unordered_map<std::string, uint32_t> material_map;
    std::vector<Material> materials;
    std::vector<Material_Handle> material_handles;
    std::vector<uint32_t> free_handles;
    uint32_t next_idx;
} material_manager_t;

material_manager_t* material_manager = NULL;

Rc_t init( void )
{
    material_manager = new (std::nothrow) material_manager_t;
    if ( material_manager == NULL ) {
        return MEMORY_ALLOC_FAILED;
    }

    material_manager->material_handles.resize(MATERIAL_RESIZE_SIZE);

    for ( uint32_t ii = 0; ii < material_manager->material_handles.size(); ++ii ) {
        material_manager->material_handles[ii].phase = 0;
        material_manager->material_handles[ii].index = ii;
    }

    material_manager->materials.resize(MATERIAL_RESIZE_SIZE);

    material_manager->next_idx = 1;

    return SUCCESS;
}

Material_Handle register_material( std::string material_name, Material material )
{
    std::unordered_map<std::string, uint32_t>::const_iterator ele = material_manager->material_map.find(material_name);
    if ( ele == material_manager->material_map.end() ) {
        uint32_t handle_idx = 0;

        //check to see if there is a free handle
        if ( material_manager->free_handles.empty()) {
            uint32_t current_size = (uint32_t)material_manager->material_handles.size();

            //check to see if we need to expand the handle vec
            if ( material_manager->next_idx == current_size ) {
                material_manager->material_handles.resize(current_size + MATERIAL_RESIZE_SIZE);

                for ( uint32_t ii = current_size; ii < material_manager->material_handles.size(); ++ii ) {
                    material_manager->material_handles[ii].phase = 0;
                    material_manager->material_handles[ii].index = ii;
                }

                material_manager->materials.resize(current_size + MATERIAL_RESIZE_SIZE);
            }

            handle_idx = material_manager->next_idx++;
        } else {
            handle_idx = material_manager->free_handles.back();
            material_manager->free_handles.pop_back();
        }

        material_manager->materials[handle_idx] = material;
        material_manager->material_map.insert({ material_name, handle_idx });

        return material_manager->material_handles[handle_idx];
    } else {

        return material_manager->material_handles[ele->second];

    }
}

Material_Handle get_material_handle( std::string material_name )
{
    std::unordered_map<std::string, uint32_t>::const_iterator ele = material_manager->material_map.find(material_name);
    if ( ele != material_manager->material_map.end() ) {
        return material_manager->material_handles[ele->second];
    }

    return material_manager->material_handles[0];
}

Material* get_material( Material_Handle handle )
{
    if ( handle.id == material_manager->material_handles[handle.index].id ) {
        return &material_manager->materials[handle.index];
    } else {
        LOG_ERROR("Stale material handle")
        return &material_manager->materials[0];
    }
}

Material* get_material( std::string material_name )
{
    std::unordered_map<std::string, uint32_t>::const_iterator ele = material_manager->material_map.find(material_name);
    if ( ele == material_manager->material_map.end() ) {
        return get_material(material_manager->material_handles[ele->second]);
    }

    LOG_ERROR(material_name << " is not a valid material name");
    return &material_manager->materials[0];
}

} // end namespace Material_Manager
} // end namespace Engine
