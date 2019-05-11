#include "Engine.h"
#include "core_common.h"

namespace Engine {

#define NUM_VERTS_PER_PARTICAL 12
#define NUM_NORMS_PER_PARTICAL 12
#define NUM_INDICE_PER_PARTICAL 6

Partical_System::Partical_System()
{
    add_component(TRANSFORM_COMP);
    add_component(PARTICAL_EMITTER_COMP);
    add_component(MESH_HANDLE_COMP);
}

void Partical_System::init()
{

}

void Partical_System::update()
{
    std::vector<Transform*>* transforms = (std::vector<Transform*>*)get_data_vec(TRANSFORM_COMP);
    std::vector<Partical_Emitter*>* emitters = (std::vector<Partical_Emitter*>*)get_data_vec(PARTICAL_EMITTER_COMP);
    std::vector<Mesh_Handle*>* mesh_handles = (std::vector<Mesh_Handle*>*)get_data_vec(MESH_HANDLE_COMP);

    float dt = get_delta_time();

    Transform* transform;
    Partical_Emitter* emitter;
    Mesh_Handle* mesh_handle;

    for ( uint64_t ii = 0; ii < entity_count; ++ii ) {
        transform = transforms->at(ii);
        emitter = emitters->at(ii);
        mesh_handle = mesh_handles->at(ii);

        // need to check if another partical should be spawned.
        if ( (dt + emitter->last_spawn) >= emitter->spawn_rate ) {
            emitter->last_spawn = 0;
            Partical partical;
            partical.transform.position = transform->position;
            Engine::Vector3f main_dir(0, 10, 0);
            Engine::Vector3f random_dir((rand()%2000 - 1000.0f)/1000.0f,
                                        (rand()%2000 - 1000.0f)/1000.0f,
                                        (rand()%2000 - 1000.0f)/1000.0f);
            partical.speed = (main_dir + (random_dir * 1.5f)) * 0.5;
            partical.life = 0;
            emitter->particals.push_back(partical);
        } else {
            emitter->last_spawn += dt;
        }

        for ( std::vector<Partical>::iterator it = emitter->particals.begin(); it != emitter->particals.end(); ) {
            // update the partical based on the speed
            Partical* partical = &(*it);
            if ( partical->life >= emitter->life_time ) {
               emitter->particals.erase(it);
            } else {
               partical->speed += Engine::Vector3f(0, -9.81, 0) * dt * 0.5f;
               partical->transform.position += partical->speed * dt;
               partical->life += dt;

               ++it;
            }
        }

        Mesh* mesh = &emitter->mesh;
        mesh->vertices = (float*)realloc(mesh->vertices, (sizeof(float) * NUM_VERTS_PER_PARTICAL * emitter->particals.size()));
        mesh->normals = (float*)realloc(mesh->normals, (sizeof(float) * NUM_NORMS_PER_PARTICAL * emitter->particals.size()));
        mesh->indices = (uint32_t*)realloc(mesh->indices, (sizeof(float) * NUM_INDICE_PER_PARTICAL * emitter->particals.size()));

        uint32_t vert_idx = 0;
        uint32_t indic_idx = 0;
        uint32_t indic_count = 0;
        uint32_t norm_idx = 0;

        //gen the mesh here
        for ( uint64_t jj = 0; jj < emitter->particals.size(); ++jj ) {
            Vector3f bottom_left;

            bottom_left.x = emitter->particals[jj].transform.position.x - emitter->width;
            bottom_left.y = emitter->particals[jj].transform.position.y - emitter->height;
            bottom_left.z = emitter->particals[jj].transform.position.z;

            mesh->vertices[vert_idx++] = bottom_left.x;
            mesh->vertices[vert_idx++] = bottom_left.y;
            mesh->vertices[vert_idx++] = bottom_left.z;

            mesh->vertices[vert_idx++] = bottom_left.x;
            mesh->vertices[vert_idx++] = bottom_left.y + emitter->height;
            mesh->vertices[vert_idx++] = bottom_left.z;

            mesh->vertices[vert_idx++] = bottom_left.x + emitter->width;
            mesh->vertices[vert_idx++] = bottom_left.y + emitter->height;
            mesh->vertices[vert_idx++] = bottom_left.z;

            mesh->vertices[vert_idx++] = bottom_left.x + emitter->width;
            mesh->vertices[vert_idx++] = bottom_left.y;
            mesh->vertices[vert_idx++] = bottom_left.z;

            mesh->indices[indic_idx++] = indic_count;
            mesh->indices[indic_idx++] = indic_count + 1;
            mesh->indices[indic_idx++] = indic_count + 2;
            mesh->indices[indic_idx++] = indic_count + 2;
            mesh->indices[indic_idx++] = indic_count + 3;
            mesh->indices[indic_idx++] = indic_count;
            indic_count += 4;

            mesh->normals[norm_idx++] = 0;
            mesh->normals[norm_idx++] = 0;
            mesh->normals[norm_idx++] = 1;
            mesh->normals[norm_idx++] = 0;
            mesh->normals[norm_idx++] = 0;
            mesh->normals[norm_idx++] = 1;
            mesh->normals[norm_idx++] = 0;
            mesh->normals[norm_idx++] = 0;
            mesh->normals[norm_idx++] = 1;
            mesh->normals[norm_idx++] = 0;
            mesh->normals[norm_idx++] = 0;
            mesh->normals[norm_idx++] = 1;
        }

        mesh->indices_count = indic_idx;
        mesh->vertices_count = vert_idx;
        mesh->normals_count = norm_idx;


        if ( update_mesh( *mesh_handle, mesh ) != 0 ) {
             LOG("Update Failed");
        }

    }
}

void Partical_System::shutdown()
{

}

} // end namespace Engine
