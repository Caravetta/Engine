#include <Engine.h>
#include <iostream>
#include "components.h"
#include "systems.h"

int main()
{
    Engine::engine_config_t engine_config;
    engine_config.window_width = 800;
    engine_config.window_height = 800;
    engine_config.window_title = "Test Window";

    Engine::Rc_t rc = Engine::init(&engine_config);
    if ( rc != Engine::SUCCESS ) {
        return 1;
    }

    Engine::register_component<Bullet_Spawner>();
    Engine::register_component<Engine::Transform>();
    Engine::register_component<Engine::Mesh_Handle>();
    Engine::register_component<Engine::Shader_ID>();
    Engine::register_component<Player>();
    Engine::register_component<Bullet_Motion>();
    Engine::register_component<Bullet_Distance>();
    Engine::register_component<Engine::Entity>();
    Engine::register_component<Camera_Info>();

    Engine::register_system<Player_System>();
    Engine::register_system<Bullet_Spawn_System>();
    Engine::register_system<Bullet_Motion_System>();
    Engine::register_system<Camera_System>();
    Engine::register_system<Engine::Mesh_Render_System>();

    Engine::register_asset<Engine::Mesh_Asset>("cube_mesh", "res/cube.mesh");
    Engine::register_asset<Engine::Mesh_Asset>("dagger_mesh", "res/Dagger.obj");
    Engine::register_asset<Engine::Vertex_Shader_Asset>("default_vert", "res/shader/model_vert_shader.glsl");
    Engine::register_asset<Engine::Fragment_Shader_Asset>("default_frag", "res/shader/model_frag_shader.glsl");

    Engine::Vertex_Shader_Asset* default_vert = Engine::get_asset_by_name<Engine::Vertex_Shader_Asset>("default_vert");
    Engine::Fragment_Shader_Asset* default_frag = Engine::get_asset_by_name<Engine::Fragment_Shader_Asset>("default_frag");

    unsigned int default_program;
    Engine::create_shader_program(default_vert->id, default_frag->id, &default_program);

    Engine::Archetype ship_arche;
    ship_arche.add_component<Engine::Transform>();
    ship_arche.add_component<Engine::Mesh_Handle>();
    ship_arche.add_component<Engine::Shader_ID>();
    ship_arche.add_component<Player>();
    ship_arche.add_component<Bullet_Spawner>();
    Engine::register_archetype(ship_arche, "ship_entity");


    Engine::Archetype bullet_arche;
    bullet_arche.add_component<Engine::Transform>();
    bullet_arche.add_component<Engine::Mesh_Handle>();
    bullet_arche.add_component<Engine::Shader_ID>();
    bullet_arche.add_component<Bullet_Motion>();
    bullet_arche.add_component<Engine::Entity>();
    bullet_arche.add_component<Bullet_Distance>();
    Engine::register_archetype(bullet_arche, "bullet_entity");

    Engine::Archetype camera_arche;
    camera_arche.add_component<Camera_Info>();
    Engine::register_archetype(camera_arche, "camera_entity");

    Engine::Transform* transform;
    Engine::Mesh_Handle* mesh_handle;
    Engine::Shader_ID* shader_id;
    Player* player;
    Camera_Info* camera_info;


    Engine::Mesh_Asset* dagger_mesh = Engine::get_asset_by_name<Engine::Mesh_Asset>("dagger_mesh");
    Engine::Mesh_Handle dagger_handle = Engine::load_to_graphics_api(&dagger_mesh->mesh);
    dagger_mesh->mesh.handle = dagger_handle;

    Engine::Mesh_Asset* cube_mesh = Engine::get_asset_by_name<Engine::Mesh_Asset>("cube_mesh");
    Engine::Mesh_Handle cube_handle = Engine::load_to_graphics_api(&cube_mesh->mesh);
    cube_mesh->mesh.handle = cube_handle;

    Engine::Entity ship = Engine::create_entity("ship_entity");

    transform = Engine::get_component<Engine::Transform>(ship);
    mesh_handle = Engine::get_component<Engine::Mesh_Handle>(ship);
    shader_id = Engine::get_component<Engine::Shader_ID>(ship);
    player = Engine::get_component<Player>(ship);
    player->name = "square";

    transform->position = Engine::Vector3f(0, 0, -1);
    transform->scale = Engine::Vector3f(0.25, 0.25, 0.25);

    *mesh_handle = cube_mesh->mesh.handle;

    shader_id->program_id = default_program;

    Engine::Entity camera = Engine::create_entity("camera_entity");
    camera_info = Engine::get_component<Camera_Info>(camera);
    camera_info->camera.field_of_view = 90.0f;
    camera_info->camera.field_of_view = 90.0f;
    camera_info->camera.aspect_ratio = 4 / 3;
    camera_info->camera.near_plane = 0.01f;
    camera_info->camera.far_plane = 10000.0f;

    camera_info->camera_type = MAIN_CAM_TYPE;

    camera_info->camera.transform.position = Engine::Vector3f(0, 0.5, 0);

    Engine::set_active_camera(&camera_info->camera);

    Engine::run();

    return 0;
}
