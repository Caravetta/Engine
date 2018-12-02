#include <Engine.h>
#include <iostream>
#include "motion.h"

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

    Engine::register_component<Engine::Transform>();
    Engine::register_component<Engine::Mesh_Handle>();
    Engine::register_component<Engine::Shader_ID>();
    Engine::register_component<Motion>();

    Engine::register_system<Motion_System>();
    Engine::register_system<Engine::Mesh_Render_System>();

    Engine::register_asset<Engine::Mesh_Asset>("cube_mesh", "res/cube.mesh");
    Engine::register_asset<Engine::Vertex_Shader_Asset>("cube_vert", "res/shader/model_vert_shader.glsl");
    Engine::register_asset<Engine::Fragment_Shader_Asset>("cube_frag", "res/shader/model_frag_shader.glsl");

    Engine::Vertex_Shader_Asset* cube_vert = Engine::get_asset_by_name<Engine::Vertex_Shader_Asset>("cube_vert");
    Engine::Fragment_Shader_Asset* cube_frag = Engine::get_asset_by_name<Engine::Fragment_Shader_Asset>("cube_frag");

    unsigned int cube_program;
    Engine::create_shader_program(cube_vert->id, cube_frag->id, &cube_program);

    Engine::Archetype cube_arche;
    cube_arche.add_component<Engine::Transform>();
    cube_arche.add_component<Engine::Mesh_Handle>();
    cube_arche.add_component<Engine::Shader_ID>();
    cube_arche.add_component<Motion>();
    Engine::register_archetype(cube_arche, "cube_entity");

    float af = 5.0f;
    float vf = -4.0f;

    Engine::Transform* transform;
    Engine::Mesh_Handle* mesh_handle;
    Engine::Shader_ID* shader_id;
    Motion* motion;

    Engine::Mesh_Asset* cube_mesh = Engine::get_asset_by_name<Engine::Mesh_Asset>("cube_mesh");
    Engine::Mesh_Handle cube_handle = Engine::load_to_graphics_api(&cube_mesh->mesh);

    for ( int ii = 0; ii < 50000; ++ii ) {
        Engine::Entity cube = Engine::create_entity("cube_entity");

        transform = Engine::get_component<Engine::Transform>(cube);
        mesh_handle = Engine::get_component<Engine::Mesh_Handle>(cube);
        shader_id = Engine::get_component<Engine::Shader_ID>(cube);
        motion = Engine::get_component<Motion>(cube);

        transform->position = Engine::Vector3f(0, 0, 0);

        cube_mesh->mesh.handle = cube_handle;
        *mesh_handle = cube_mesh->mesh.handle;

        shader_id->program_id = cube_program;

        motion->acceleration = Engine::Vector3f(randf(-af, af), randf(-af, af), randf(-af, af));
        motion->velocity = motion->acceleration * vf;
    }

    Engine::Camera camera(Engine::Vector3f(67, 8, 32), Engine::Vector2f(800, 800));
    camera.rotate(30.29, -0.2);
    Engine::set_active_camera(&camera);

    Engine::run();

    return 0;
}
