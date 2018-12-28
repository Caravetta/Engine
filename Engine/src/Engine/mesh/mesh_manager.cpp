#include <vector>
#include "mesh_manager.h"

namespace Engine {
namespace Mesh_Manager {

#define MESH_RESIZE_SIZE 100

typedef struct {
    std::vector<Mesh_Handle> mesh_handles;
    std::vector<uint32_t> indice_data;
    std::vector<uint32_t> free_handles;
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

    mesh_manager->next_idx = 0;

    return SUCCESS;
}

vao_t* get_mesh_vao( Mesh_Handle handle )
{
    UNUSED_ARG(handle);
    return &Mesh_Manager::mesh_manager->vaos[handle.index];
}

uint32_t get_indices_count( Mesh_Handle handle )
{
    UNUSED_ARG(handle);
    return Mesh_Manager::mesh_manager->indice_data[handle.index];;
}

} // end namespace Mesh_Manager

Mesh_Handle load_to_graphics_api( Mesh* mesh )
{
    uint32_t handle_idx = 0;

    if ( Mesh_Manager::mesh_manager->free_handles.empty() ) {
        //check to see if we need to expand the mesh handle vec
        uint32_t current_size = (uint32_t)Mesh_Manager::mesh_manager->mesh_handles.size();
        if ( Mesh_Manager::mesh_manager->next_idx == current_size ) {
            //TODO(JOSH): need to check if we have hit uint32_t max

            Mesh_Manager::mesh_manager->mesh_handles.resize(current_size + MESH_RESIZE_SIZE);

            for ( uint32_t ii = current_size; ii < Mesh_Manager::mesh_manager->mesh_handles.size(); ++ii ) {
                Mesh_Manager::mesh_manager->mesh_handles[ii].phase = 0;
                Mesh_Manager::mesh_manager->mesh_handles[ii].index = ii;
            }

            Mesh_Manager::mesh_manager->vaos.resize(current_size + MESH_RESIZE_SIZE);
            Mesh_Manager::mesh_manager->indice_data.resize(current_size + MESH_RESIZE_SIZE);
        }

        handle_idx = Mesh_Manager::mesh_manager->next_idx++;
    } else {
        handle_idx = Mesh_Manager::mesh_manager->free_handles.back();
        Mesh_Manager::mesh_manager->free_handles.pop_back();
    }

    Mesh_Manager::mesh_manager->indice_data[handle_idx] = mesh->indices_count;

    // create a vao for this mesh
    vao_t* vao = &Mesh_Manager::mesh_manager->vaos[handle_idx];


    LOG("vert count " << mesh->vertices_count << " norm count " << mesh->normals_count);
    create_vao(vao);
    bind_vao(vao);
    create_index_buffer(vao, (int*)mesh->indices, (int)mesh->indices_count, STATIC_DRAW); //TODO: need to get ride of this cast
    create_float_attribute(vao, 0, mesh->vertices, mesh->vertices_count * sizeof(float), 3, 3 * sizeof(float), 0, STATIC_DRAW);
    create_float_attribute(vao, 1, mesh->normals, mesh->normals_count * sizeof(float), 3, 3 * sizeof(float), 0, STATIC_DRAW);
    create_float_attribute(vao, 2, mesh->textures, mesh->textures_count * sizeof(float), 2, 2 * sizeof(float), 0, STATIC_DRAW);
    unbind_vao();

    return Mesh_Manager::mesh_manager->mesh_handles[handle_idx];
}

Rc_t deload_from_graphics_api( Mesh_Handle handle )
{
    UNUSED_ARG(handle);
    return SUCCESS;
}

} // end namespace Engine
