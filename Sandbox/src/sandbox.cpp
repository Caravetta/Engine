#include <Engine.h>
#include <iostream>
#include "motion.h"
#include "debug_camera.h"

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
    Engine::register_component<Engine::Text>();
    Engine::register_component<Engine::Font_Settings>();
    Engine::register_component<Engine::Texture>();
    Engine::register_component<Motion>();

    Engine::register_system<Motion_System>();
    Engine::register_system<Engine::Mesh_Render_System>();

    Engine::register_asset<Engine::Mesh_Asset>("cube_mesh", "res/cube.mesh");
    Engine::register_asset<Engine::Mesh_Asset>("dagger", "res/Dagger.obj");
    Engine::register_asset<Engine::Vertex_Shader_Asset>("cube_vert", "res/shader/model_vert_shader.glsl");
    Engine::register_asset<Engine::Fragment_Shader_Asset>("cube_frag", "res/shader/model_frag_shader.glsl");
    Engine::register_asset<Engine::Font_Asset>("default_font", "res/font/arial.ttf");

    Engine::Vertex_Shader_Asset* cube_vert = Engine::get_asset_by_name<Engine::Vertex_Shader_Asset>("cube_vert");
    Engine::Fragment_Shader_Asset* cube_frag = Engine::get_asset_by_name<Engine::Fragment_Shader_Asset>("cube_frag");
    Engine::Font_Asset* default_font = Engine::get_asset_by_name<Engine::Font_Asset>("default_font");

    unsigned int cube_program;
    Engine::create_shader_program(cube_vert->id, cube_frag->id, &cube_program);

    Engine::Archetype cube_arche;
    cube_arche.add_component<Engine::Transform>();
    cube_arche.add_component<Engine::Mesh_Handle>();
    cube_arche.add_component<Engine::Shader_ID>();
    cube_arche.add_component<Motion>();
    Engine::register_archetype(cube_arche, "cube_entity");

    Engine::Archetype text_arche;
    text_arche.add_component<Engine::Mesh_Handle>();
    text_arche.add_component<Engine::Shader_ID>();
    text_arche.add_component<Engine::Texture>();
    text_arche.add_component<Engine::Text>();
    text_arche.add_component<Engine::Font_Settings>();
    text_arche.add_component<Engine::Transform>();
    Engine::register_archetype(text_arche, "text_entity");

    float af = 5.0f;
    float vf = -4.0f;

    af = 0;
    vf = 0;

    Engine::Transform* transform;
    Engine::Mesh_Handle* mesh_handle;
    Engine::Shader_ID* shader_id;
    Engine::Texture* texture;
    Engine::Font_Settings* font_settings;
    Engine::Text* text;
    Motion* motion;

    Engine::Mesh_Asset* cube_mesh = Engine::get_asset_by_name<Engine::Mesh_Asset>("dagger");
    Engine::Mesh_Handle cube_handle = Engine::load_to_graphics_api(&cube_mesh->mesh);

    Engine::Entity first;

    for ( int ii = 0; ii < 2; ++ii ) {
        Engine::Entity cube = Engine::create_entity("cube_entity");

        if ( ii == 0 ) {
            first = cube;
        }

        transform = Engine::get_component<Engine::Transform>(cube);
        mesh_handle = Engine::get_component<Engine::Mesh_Handle>(cube);
        shader_id = Engine::get_component<Engine::Shader_ID>(cube);
        motion = Engine::get_component<Motion>(cube);

        if ( ii == 0 ) {
            transform->position = Engine::Vector3f(0, 0, 0);
        } else {
            transform->position = Engine::Vector3f(20, 0, 0);
        }

        cube_mesh->mesh.handle = cube_handle;
        *mesh_handle = cube_mesh->mesh.handle;

        shader_id->program_id = cube_program;

        motion->acceleration = Engine::Vector3f(randf(-af, af), randf(-af, af), randf(-af, af));
        motion->velocity = motion->acceleration * vf;

        //Engine::delete_entity(cube);
    }
    //Engine::delete_entity(first);

    Engine::Entity text_entity = Engine::create_entity("text_entity");
    Engine::Font_Asset* test_font = Engine::get_asset_by_name<Engine::Font_Asset>("default_font");

    texture = Engine::get_component<Engine::Texture>(text_entity);
    texture->id = get_font_texture_id(test_font->handle, 2);

    font_settings = Engine::get_component<Engine::Font_Settings>(text_entity);
    font_settings->size = 2;
    font_settings->font_handle = test_font->handle;
    font_settings->string_new_line_pad = 1;

    text = Engine::get_component<Engine::Text>(text_entity);
    *text = "JOSH";

    transform = Engine::get_component<Engine::Transform>(text_entity);
    transform->position = Engine::Vector3f(0, 0, 0);

    mesh_handle = Engine::get_component<Engine::Mesh_Handle>(text_entity);
    *mesh_handle = generate_text_mesh(text, font_settings);

    shader_id = Engine::get_component<Engine::Shader_ID>(text_entity);
    shader_id->program_id = cube_program;





    //Engine::Camera camera(Engine::Vector3f(0, 0, 5), Engine::Vector2f(800, 800));
    //camera.rotate(30.29, -0.2);
    //camera.rotate(0, 0);
    debug_camera_init();
    Engine::Camera* camera = get_debug_camera();
    //camera->rotate(30.29, -0.2);
    Engine::set_active_camera(camera);

    Engine::run();

    return 0;
}
