#include <Engine.h>
#include <iostream>
#include "debug_camera.h"
#include "components.h"
#include "systems.h"
#include "input_tracker.h"

template<typename T, typename U>
static T lerp(const T& val1, const T& val2, const U& amt)
{
    return (T)(val1 * ((U)(1) - amt) + val2 * amt);
}

inline float randf()
{
    return ::rand()/(float)RAND_MAX;
}
inline float randf(float min, float max) {
    return lerp(min, max, randf());
}

int main()
{
    Engine::engine_config_t engine_config;
    engine_config.window_width = 1000;
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

    //Engine::register_system<Motion_System>();
    Engine::register_system<Player_System>();
    Engine::register_system<Bullet_Spawn_System>();
    Engine::register_system<Bullet_Motion_System>();
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

    Engine::Transform* transform;
    Engine::Mesh_Handle* mesh_handle;
    Engine::Shader_ID* shader_id;

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

    transform->position = Engine::Vector3f(0, 0, 0);
    transform->scale = Engine::Vector3f(0.5, 0, 0);

    *mesh_handle = cube_mesh->mesh.handle;

    shader_id->program_id = default_program;

    Engine::Camera camera(Engine::Vector3f(0, 2.6212, 1.21776), Engine::Vector2f(800, 800));
    camera.rotate(0, -0.89);

    //debug_camera_init();
    //Engine::Camera* camera = get_debug_camera();

    Engine::set_active_camera(&camera);

    Input_Tracker::init();

    Engine::run();

    return 0;
}
