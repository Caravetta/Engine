#include "systems.h"
#include "components.h"
#include "input_tracker.h"

Bullet_Spawn_System::Bullet_Spawn_System()
{
    name = "Bullet_Spawn_System";
    add_component<Engine::Transform>();
    add_component<Bullet_Spawner>();
    add_component<Engine::Shader_ID>();
}

void Bullet_Spawn_System::init()
{

}

void Bullet_Spawn_System::update()
{
    std::vector<Engine::Transform*>* transform_vec = get_data_vec<Engine::Transform>();
    std::vector<Bullet_Spawn_System*>* bullet_spawn_vec = get_data_vec<Bullet_Spawn_System>();
    std::vector<Engine::Shader_ID*>* shader_vec = get_data_vec<Engine::Shader_ID>();

    Engine::Transform* transform;
    Bullet_Spawner* spawner;
    Engine::Shader_ID* shader_id;

    for( uint32_t ii = 0; ii < entity_count; ++ii ) {

        transform = transform_vec->at(ii);
        shader_id = shader_vec->at(ii);

        if ( is_key_pressed(Input_Tracker::D_KEY_STATE) ) {
            Engine::Entity bullet = Engine::create_entity("bullet_entity");

            Engine::Transform* bullet_transform;
            Engine::Mesh_Handle* mesh_handle;
            Engine::Shader_ID* bullet_shader_id;
            Bullet_Motion* bullet_motion;
            Bullet_Distance* bullet_distance;
            Engine::Entity* bullet_entity_id;

            Engine::Mesh_Asset* dagger_mesh = Engine::get_asset_by_name<Engine::Mesh_Asset>("dagger_mesh");

            bullet_transform = Engine::get_component<Engine::Transform>(bullet);
            mesh_handle = Engine::get_component<Engine::Mesh_Handle>(bullet);
            bullet_shader_id = Engine::get_component<Engine::Shader_ID>(bullet);
            bullet_motion = Engine::get_component<Bullet_Motion>(bullet);
            bullet_distance = Engine::get_component<Bullet_Distance>(bullet);
            bullet_entity_id = Engine::get_component<Engine::Entity>(bullet);

            bullet_transform->position = transform->position;
            bullet_transform->scale = Engine::Vector3f(0.005, 0, 0);
            bullet_transform->rotation = Engine::Vector3f(-90, 0, 0);
            *mesh_handle = dagger_mesh->mesh.handle;
            bullet_motion->acceleration = Engine::Vector3f(0, 0, -1);
            bullet_motion->velocity = bullet_motion->acceleration * 20.0f;
            bullet_shader_id->program_id = shader_id->program_id;
            *bullet_entity_id = bullet;
            bullet_distance->max_distance = 20;

        }
    }
}

void Bullet_Spawn_System::shutdown()
{

}
