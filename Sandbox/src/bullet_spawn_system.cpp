#include "systems.h"
#include "components.h"

Bullet_Spawn_System::Bullet_Spawn_System()
{
    name = "Bullet_Spawn_System";
    add_component<Engine::Transform>();
    add_component<Bullet_Spawner>();
}

void Bullet_Spawn_System::init()
{

}

void Bullet_Spawn_System::update()
{
    std::vector<Engine::Transform*>* transform_vec = get_data_vec<Engine::Transform>();

    Engine::Transform* transform;

    for( uint32_t ii = 0; ii < entity_count; ++ii ) {

        transform = transform_vec->at(ii);

        if ( Engine::is_key_pressed(Engine::KEY_SPACE) ) {
            Engine::Entity bullet = Engine::create_entity("bullet_entity");
            Engine::Transform* bullet_transform;
            Engine::Mesh_Handle* mesh_handle;
            Bullet_Motion* bullet_motion;
            Bullet_Distance* bullet_distance;
            Engine::Entity* bullet_entity_id;
            Engine::Material_Handle* material_handle;

            Engine::Mesh_Asset* dagger_mesh = Engine::get_asset_by_name<Engine::Mesh_Asset>("dagger_mesh");

            bullet_transform = Engine::get_component<Engine::Transform>(bullet);
            mesh_handle = Engine::get_component<Engine::Mesh_Handle>(bullet);
            bullet_motion = Engine::get_component<Bullet_Motion>(bullet);
            bullet_distance = Engine::get_component<Bullet_Distance>(bullet);
            bullet_entity_id = Engine::get_component<Engine::Entity>(bullet);
            material_handle = Engine::get_component<Engine::Material_Handle>(bullet);

            bullet_transform->position = Engine::Vector3f(transform->position.x, transform->position.y, transform->position.z);
            bullet_transform->scale = Engine::Vector3f(0.009, 0.009, 0.009);
            bullet_transform->rotation = Engine::Vector3f(-90, 0, 0);
            *mesh_handle = dagger_mesh->mesh.handle;
            bullet_motion->acceleration = Engine::Vector3f(0, 0, -1);
            bullet_motion->velocity = bullet_motion->acceleration * 20.0f;
            *material_handle = Engine::get_material_handle( "dagger_mat" );
            *bullet_entity_id = bullet;
            bullet_distance->max_distance = 20;

        }
    }
}

void Bullet_Spawn_System::shutdown()
{

}
