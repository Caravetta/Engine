#include <vector>
#include "mesh_manager.h"

namespace Engine {
namespace Mesh_Manager {

#define MESH_RESIZE_SIZE 100
#define RESERVED_MESH_HANDLE 0

typedef struct {
    std::vector<Mesh_Handle> mesh_handles;
    std::vector<uint32_t> indice_data;
    std::vector<uint32_t> free_handles;
    std::vector<bool> is_dynamic_vec;
    std::vector<vao_t> vaos;
    uint32_t next_idx;
} mesh_manager_t;

mesh_manager_t* mesh_manager = NULL;

Rc_t init( void ) {
    mesh_manager = new (std::nothrow) mesh_manager_t;
    if ( mesh_manager == NULL ) {
        return MEMORY_ALLOC_FAILED;
    }

    mesh_manager->mesh_handles.resize(MESH_RESIZE_SIZE);

    for ( uint32_t ii = 0; ii < mesh_manager->mesh_handles.size(); ++ii ) {
        mesh_manager->mesh_handles[ii].phase = 0;
        mesh_manager->mesh_handles[ii].index = ii;
    }

    mesh_manager->vaos.resize(MESH_RESIZE_SIZE);
    mesh_manager->indice_data.resize(MESH_RESIZE_SIZE);
    mesh_manager->is_dynamic_vec.resize(MESH_RESIZE_SIZE);

    mesh_manager->next_idx = 1;

    return SUCCESS;
}

vao_t* get_mesh_vao( Mesh_Handle handle )
{
    if ( handle.id != RESERVED_MESH_HANDLE &&
        (handle.id == mesh_manager->mesh_handles[handle.index].id) ) {
        return &mesh_manager->vaos[handle.index];
    }

    return NULL;
}

uint32_t get_indices_count( Mesh_Handle handle )
{
    if ( handle.id != RESERVED_MESH_HANDLE &&
        (handle.id == mesh_manager->mesh_handles[handle.index].id) ) {
        return mesh_manager->indice_data[handle.index];
    }

    return 0;
}

Mesh_Handle load_to_graphics_api( Mesh* mesh, mesh_usage_t usage_type )
{
    uint32_t handle_idx = 0;

    if ( mesh_manager->free_handles.empty() ) {
        //check to see if we need to expand the mesh handle vec
        uint32_t current_size = (uint32_t)mesh_manager->mesh_handles.size();
        if ( mesh_manager->next_idx == current_size ) {
            //TODO(JOSH): need to check if we have hit uint32_t max

            mesh_manager->mesh_handles.resize(current_size + MESH_RESIZE_SIZE);

            for ( uint32_t ii = current_size; ii < mesh_manager->mesh_handles.size(); ++ii ) {
                mesh_manager->mesh_handles[ii].phase = 0;
                mesh_manager->mesh_handles[ii].index = ii;
            }

            mesh_manager->vaos.resize(current_size + MESH_RESIZE_SIZE);
            mesh_manager->indice_data.resize(current_size + MESH_RESIZE_SIZE);
            mesh_manager->is_dynamic_vec.resize(current_size + MESH_RESIZE_SIZE);
        }

        handle_idx = mesh_manager->next_idx++;
    } else {
        handle_idx = mesh_manager->free_handles.back();
        mesh_manager->free_handles.pop_back();
    }

    mesh_manager->indice_data[handle_idx] = mesh->indices_count;

    switch( usage_type ) {
    case MESH_STATIC_DRAW: {
        mesh_manager->is_dynamic_vec[handle_idx] = false;
    } break;
    case MESH_DYNAMIC_DRAW: {
        mesh_manager->is_dynamic_vec[handle_idx] = true;
    } break;
    default: {
        LOG_ERROR( "Not a valid mesh usage type.");
    } break;
    }

    // create a vao for this mesh
    vao_t* vao = &mesh_manager->vaos[handle_idx];

    create_vao(vao);
    bind_vao(vao);
    create_index_buffer(vao, (int*)mesh->indices, (int)mesh->indices_count, (usage_type_t)usage_type); //TODO: need to get ride of this cast
    create_float_attribute(vao, 0, mesh->vertices, mesh->vertices_count * sizeof(float), 3, 3 * sizeof(float), 0, (usage_type_t)usage_type);
    create_float_attribute(vao, 2, mesh->normals, mesh->normals_count * sizeof(float), 3, 3 * sizeof(float), 0, (usage_type_t)usage_type);
    create_float_attribute(vao, 5, mesh->textures, mesh->textures_count * sizeof(float), 2, 2 * sizeof(float), 0, (usage_type_t)usage_type);
    unbind_vao();

    return mesh_manager->mesh_handles[handle_idx];
}

Rc_t update_mesh( Mesh_Handle handle, Mesh* mesh )
{
    if ( handle.id == mesh_manager->mesh_handles[handle.index].id ) {
        if ( mesh_manager->is_dynamic_vec[handle.index] ) {
            vao_t* vao = &mesh_manager->vaos[handle.index];

            update_index_buffer(vao, (int*)mesh->indices, (int)mesh->indices_count, DYNAMIC_DRAW);
            update_float_attribute(vao, 0, mesh->vertices, mesh->vertices_count * sizeof(float), DYNAMIC_DRAW);
            update_float_attribute(vao, 2, mesh->normals, mesh->normals_count * sizeof(float), DYNAMIC_DRAW);
            update_float_attribute(vao, 5, mesh->textures, mesh->textures_count * sizeof(float), DYNAMIC_DRAW);
            return SUCCESS;
        }
        return MESH_IS_NOT_DYNAMIC;
    }
    return INVALID_HANDLE;
}

Rc_t deload_from_graphics_api( Mesh_Handle handle )
{
    UNUSED_ARG(handle); //TODO(JOSH): need to check handle to make sure it matches
    return SUCCESS;
}

} // end namespace Mesh_Manager
} // end namespace Engine

