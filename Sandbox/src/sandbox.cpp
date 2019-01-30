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

    // Register all components
    Engine::register_component<Bullet_Spawner>();
    Engine::register_component<Engine::Transform>();
    Engine::register_component<Engine::Mesh_Handle>();
    Engine::register_component<Player>();
    Engine::register_component<Bullet_Motion>();
    Engine::register_component<Bullet_Distance>();
    Engine::register_component<Engine::Entity>();
    Engine::register_component<Camera_Info>();
    Engine::register_component<Engine::Material_Handle>();

    // Register systems NOTE: systems will execute is order registered
    Engine::register_system<Player_System>();
    Engine::register_system<Bullet_Spawn_System>();
    Engine::register_system<Bullet_Motion_System>();
    Engine::register_system<Camera_System>();
    Engine::register_system<Engine::Mesh_Render_System>();

    // Register all assets
    Engine::register_asset<Engine::Mesh_Asset>("cube_mesh", "res/cube1.obj");
    Engine::register_asset<Engine::Mesh_Asset>("dagger_mesh", "res/Dagger.obj");
    Engine::register_asset<Engine::Vertex_Shader_Asset>("default_vert", "res/shader/model_vert_shader.glsl");
    Engine::register_asset<Engine::Fragment_Shader_Asset>("default_frag", "res/shader/model_frag_shader.glsl");
    Engine::register_asset<Engine::Fragment_Shader_Asset>("dagger_frag", "res/shader/dagger_frag_shader.glsl");
    Engine::register_asset<Engine::Vertex_Shader_Asset>("dagger_vert", "res/shader/dagger_vert_shader.glsl");
    Engine::register_asset<Engine::Texture_Asset>("dagger_texture", "res/Dagger_Specular.tga");
    Engine::register_asset<Engine::Texture_Asset>("dagger_normals", "res/Dagger_Normals.tga");
    Engine::register_asset<Engine::Texture_Asset>("ship_texture", "res/uvmap.tga");

    Engine::Vertex_Shader_Asset* default_vert = Engine::get_asset_by_name<Engine::Vertex_Shader_Asset>("default_vert");
    Engine::Fragment_Shader_Asset* default_frag = Engine::get_asset_by_name<Engine::Fragment_Shader_Asset>("default_frag");

    Engine::Vertex_Shader_Asset* dagger_vert = Engine::get_asset_by_name<Engine::Vertex_Shader_Asset>("dagger_vert");
    Engine::Fragment_Shader_Asset* dagger_frag = Engine::get_asset_by_name<Engine::Fragment_Shader_Asset>("dagger_frag");

    // Load Assets to the Graphics card
    unsigned int default_program;
    Engine::create_shader_program(default_vert->id, default_frag->id, &default_program);

    unsigned int dagger_program;
    Engine::create_shader_program(dagger_vert->id, dagger_frag->id, &dagger_program);

    Engine::Texture_Asset* dagger_texture = Engine::get_asset_by_name<Engine::Texture_Asset>("dagger_texture");
    dagger_texture->texture.handle = Engine::load_texture_to_graphics_api(&dagger_texture->texture);

    Engine::Texture_Asset* dagger_normals = Engine::get_asset_by_name<Engine::Texture_Asset>("dagger_normals");
    dagger_normals->texture.handle = Engine::load_texture_to_graphics_api(&dagger_normals->texture);

    Engine::Texture_Asset* ship_texture = Engine::get_asset_by_name<Engine::Texture_Asset>("ship_texture");
    ship_texture->texture.handle = Engine::load_texture_to_graphics_api(&ship_texture->texture);

    Engine::Mesh_Asset* dagger_mesh = Engine::get_asset_by_name<Engine::Mesh_Asset>("dagger_mesh");
    Engine::Mesh_Handle dagger_handle = Engine::load_to_graphics_api(&dagger_mesh->mesh);
    dagger_mesh->mesh.handle = dagger_handle;

    Engine::Mesh_Asset* cube_mesh = Engine::get_asset_by_name<Engine::Mesh_Asset>("cube_mesh");
    Engine::Mesh_Handle cube_handle = Engine::load_to_graphics_api(&cube_mesh->mesh);
    cube_mesh->mesh.handle = cube_handle;

    // Create/Register Entity Archetypes
    Engine::Archetype ship_arche;
    ship_arche.add_component<Engine::Transform>();
    ship_arche.add_component<Engine::Mesh_Handle>();
    ship_arche.add_component<Player>();
    ship_arche.add_component<Bullet_Spawner>();
    ship_arche.add_component<Engine::Material_Handle>();
    Engine::register_archetype(ship_arche, "ship_entity");

    Engine::Archetype bullet_arche;
    bullet_arche.add_component<Engine::Transform>();
    bullet_arche.add_component<Engine::Mesh_Handle>();
    bullet_arche.add_component<Bullet_Motion>();
    bullet_arche.add_component<Engine::Entity>();
    bullet_arche.add_component<Bullet_Distance>();
    bullet_arche.add_component<Engine::Material_Handle>();
    Engine::register_archetype(bullet_arche, "bullet_entity");

    Engine::Archetype camera_arche;
    camera_arche.add_component<Camera_Info>();
    Engine::register_archetype(camera_arche, "camera_entity");

    // Create/Register Materials
    Engine::Material ship_material;
    ship_material.shader_id = default_program;
    ship_material.add_element("color", Engine::VEC3_ELEMENT);
    ship_material.add_element("test", Engine::TEXT_HANDLE_ELEMENT);
    ship_material.set_element<Engine::Vector3f>("color", Engine::Vector3f(1 ,1 ,1));
    Engine::Material_Handle ship_mat_handle = Engine::register_material("ship_mat", ship_material);
    ship_material.set_element<Engine::Texture_Handle>("test", ship_texture->texture.handle);
    std::cout << "ship_mat_handle " << ship_mat_handle.id << std::endl;

    Engine::Material dagger_material;
    dagger_material.shader_id = dagger_program;
    dagger_material.add_element("color", Engine::VEC3_ELEMENT);
    dagger_material.add_element("a", Engine::TEXT_HANDLE_ELEMENT);
    dagger_material.add_element("second", Engine::TEXT_HANDLE_ELEMENT);
    //dagger_material.set_element<Engine::Vector3f>("color", Engine::Vector3f(0.501 , 0.501, 0.501));
    dagger_material.set_element<Engine::Vector3f>("color", Engine::Vector3f(1 , 1, 1));
    dagger_material.set_element<Engine::Texture_Handle>("a", dagger_texture->texture.handle);
    dagger_material.set_element<Engine::Texture_Handle>("second", dagger_normals->texture.handle);
    Engine::Material_Handle dagger_mat_handle = Engine::register_material("dagger_mat", dagger_material);
    std::cout << "dagger_mat_handle " << dagger_mat_handle.id << std::endl;

    Engine::Transform* transform;
    Engine::Mesh_Handle* mesh_handle;
    Engine::Material_Handle* material_handle;
    Player* player;
    Camera_Info* camera_info;

    // Create the ship(player) entity
    Engine::Entity ship = Engine::create_entity("ship_entity");
    transform = Engine::get_component<Engine::Transform>(ship);
    mesh_handle = Engine::get_component<Engine::Mesh_Handle>(ship);
    material_handle = Engine::get_component<Engine::Material_Handle>(ship);
    *material_handle = ship_mat_handle;
    player = Engine::get_component<Player>(ship);
    player->name = "square";

    transform->position = Engine::Vector3f(0, 0, -1);
    transform->scale = Engine::Vector3f(0.25, 0.25, 0.25);

    *mesh_handle = cube_mesh->mesh.handle;

    // Create the camera entity
    Engine::Entity camera = Engine::create_entity("camera_entity");
    camera_info = Engine::get_component<Camera_Info>(camera);
    camera_info->camera.field_of_view = 70.0f;
    camera_info->camera.aspect_ratio = 800 / 800;
    camera_info->camera.near_plane = 0.01f;
    camera_info->camera.far_plane = 10000.0f;

    camera_info->camera_type = MAIN_CAM_TYPE;

    camera_info->camera.transform.position = Engine::Vector3f(0, 0.5, 0);

    Engine::set_active_camera(&camera_info->camera);

    Engine::run();

    return 0;
}
