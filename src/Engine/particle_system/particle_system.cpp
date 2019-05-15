#include "Engine.h"
#include "core_common.h"

namespace Engine {

#define NUM_VERTS_PER_PARTICLE 12
#define NUM_NORMS_PER_PARTICLE 12
#define NUM_INDICE_PER_PARTICLE 6

Particle_System::Particle_System()
{
    add_component(TRANSFORM_COMP);
    add_component(BILLBOARD_PARTICLE_EMITTER_COMP);
    add_component(MESH_HANDLE_COMP);
}

void Particle_System::init()
{

}

void Particle_System::update()
{
    std::vector<Transform*>* transforms = (std::vector<Transform*>*)get_data_vec(TRANSFORM_COMP);
    std::vector<Billboard_Particle_Emitter*>* emitters = (std::vector<Billboard_Particle_Emitter*>*)get_data_vec(BILLBOARD_PARTICLE_EMITTER_COMP);
    std::vector<Mesh_Handle*>* mesh_handles = (std::vector<Mesh_Handle*>*)get_data_vec(MESH_HANDLE_COMP);

    float dt = get_delta_time();

    Transform* transform;
    Billboard_Particle_Emitter* emitter;
    Mesh_Handle* mesh_handle;

    for ( uint64_t ii = 0; ii < entity_count; ++ii ) {
        transform = transforms->at(ii);
        emitter = emitters->at(ii);
        mesh_handle = mesh_handles->at(ii);

        // need to check if another particle should be spawned.
        if ( (dt + emitter->last_spawn) >= emitter->spawn_rate ) {
            emitter->last_spawn = 0;
            Particle particle;
            particle.transform.position = transform->position;
            particle.life = 0;

            // sett particle life time
            switch ( emitter->life_type ) {
            case STATIC_VALUE: {
               particle.life_time = emitter->life_time.min;
            } break;
            case BETWEEN_TWO_VALUES: {
               Vector2f* life_time = &emitter->life_time;
               //particle.life_time = rand()%(life_time->max - life_time->min + 1) + life_time->min;
               particle.life_time = life_time->min + (life_time->max - life_time->min) * (rand() / RAND_MAX) / 2.0;
            } break;
            case GRADIENT_VALUE: // not sure if this should be supported
            default:
               break;
            }

            // set particle speed
            switch( emitter->start_speed_type ) {
            case STATIC_VALUE: {
               Vector2f* x_speed = &emitter->x_speed;
               Vector2f* y_speed = &emitter->y_speed;
               Vector2f* z_speed = &emitter->z_speed;
               Vector3f speed(x_speed->min, y_speed->min, z_speed->min);
               particle.speed = speed;

            } break;
            case BETWEEN_TWO_VALUES: {
               Vector2f* x_speed = &emitter->start_x_speed;
               Vector2f* y_speed = &emitter->start_y_speed;
               Vector2f* z_speed = &emitter->start_z_speed;

               particle.speed.x = between_two_floats(x_speed->min, x_speed->max);
               particle.speed.y = between_two_floats(y_speed->min, y_speed->max);
               particle.speed.z = between_two_floats(z_speed->min, z_speed->max);
            } break;
            case GRADIENT_VALUE:
            default:
              break;
            }
            //set particle start size
            switch( emitter->start_size_type ) {
            case STATIC_VALUE: {
               Vector2f* start_width = &emitter->start_width;
               Vector2f* start_height = &emitter->start_height;

               particle.size.width = start_width->min;
               particle.size.height = start_height->min;
            } break;
            case BETWEEN_TWO_VALUES: {
               Vector2f* start_width = &emitter->start_width;
               Vector2f* start_height = &emitter->start_height;

               particle.size.width = between_two_floats(start_width->min, start_width->max);
               particle.size.height = between_two_floats(start_height->min, start_height->max);
            } break;
            case GRADIENT_VALUE:
            default:
               break;
            }

            emitter->particles.push_back(particle);
        } else {
            emitter->last_spawn += dt;
        }

        for ( std::vector<Particle>::iterator it = emitter->particles.begin(); it != emitter->particles.end(); ) {
            // update the particle based on the speed
            Particle* particle = &(*it);
            if ( particle->life >= emitter->life_time.min ) {
               emitter->particles.erase(it);
            } else {
               particle->speed += Engine::Vector3f(0, -9.81, 0) * dt * 0.5f;
               particle->transform.position += particle->speed * dt;
               particle->life += dt;

               ++it;
            }
        }

        Mesh* mesh = &emitter->mesh;
        size_t num_particles = emitter->particles.size();
        mesh->vertices = (float*)realloc(mesh->vertices, (sizeof(float) * NUM_VERTS_PER_PARTICLE * num_particles));
        mesh->normals = (float*)realloc(mesh->normals, (sizeof(float) * NUM_NORMS_PER_PARTICLE * num_particles));
        mesh->indices = (uint32_t*)realloc(mesh->indices, (sizeof(float) * NUM_INDICE_PER_PARTICLE * num_particles));

        uint32_t vert_idx = 0;
        uint32_t indic_idx = 0;
        uint32_t indic_count = 0;
        uint32_t norm_idx = 0;

        //gen the mesh here
        for ( uint64_t jj = 0; jj < emitter->particles.size(); ++jj ) {
            Vector3f bottom_left;
            float width = emitter->particles[jj].size.width;
            float height = emitter->particles[jj].size.height;

            bottom_left.x = emitter->particles[jj].transform.position.x - width;
            bottom_left.y = emitter->particles[jj].transform.position.y - height;
            bottom_left.z = emitter->particles[jj].transform.position.z;

            mesh->vertices[vert_idx++] = bottom_left.x;
            mesh->vertices[vert_idx++] = bottom_left.y;
            mesh->vertices[vert_idx++] = bottom_left.z;

            mesh->vertices[vert_idx++] = bottom_left.x;
            mesh->vertices[vert_idx++] = bottom_left.y + height;
            mesh->vertices[vert_idx++] = bottom_left.z;

            mesh->vertices[vert_idx++] = bottom_left.x + width;
            mesh->vertices[vert_idx++] = bottom_left.y + height;
            mesh->vertices[vert_idx++] = bottom_left.z;

            mesh->vertices[vert_idx++] = bottom_left.x + width;
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

void Particle_System::shutdown()
{

}

} // end namespace Engine
