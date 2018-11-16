#include "user_init.h"

void user_init() {

    core::Gui::init("res/shader/gui_vert_shader.glsl", "res/shader/gui_frag_shader.glsl");

    // Register Assets
    core::Asset_Manager::register_asset<Vertex_Shader_Asset>("text_vert", "res/shader/text_vert_shader.glsl");
    core::Asset_Manager::register_asset<Fragment_Shader_Asset>("text_frag", "res/shader/text_frag_shader.glsl");
    core::Asset_Manager::register_asset<Font_Asset>("arial", "res/fonts/arial.ttf");

    core::Asset_Manager::register_asset<Mesh_Asset>("test_mesh", "res/cube.mesh");
    core::Asset_Manager::register_asset<Vertex_Shader_Asset>("mesh_vert", "res/shader/model_vert_shader.glsl");
    core::Asset_Manager::register_asset<Fragment_Shader_Asset>("mesh_frag", "res/shader/model_frag_shader.glsl");

    // Create Shaders
    Vertex_Shader_Asset* mesh_vert_asset;
    Fragment_Shader_Asset* mesh_frag_asset;
    core::Asset_Manager::get_asset<Vertex_Shader_Asset>("mesh_vert", &mesh_vert_asset);
    core::Asset_Manager::get_asset<Fragment_Shader_Asset>("mesh_frag", &mesh_frag_asset);

    unsigned int mesh_shader_program;
    core::create_shader_program(mesh_vert_asset->vertex_id, mesh_frag_asset->fragment_id, &mesh_shader_program);

    Vertex_Shader_Asset* vert_asset = NULL;
    core::Asset_Manager::get_asset<Vertex_Shader_Asset>("text_vert", &vert_asset);

    Fragment_Shader_Asset* frag_asset = NULL;
    core::Asset_Manager::get_asset<Fragment_Shader_Asset>("text_frag", &frag_asset);

    unsigned int text_shader_program;
    core::create_shader_program(vert_asset->vertex_id, frag_asset->fragment_id, &text_shader_program);

    // Register Achetypes
    core::Archetype cube_arche;
    cube_arche.add_component<Transform>();
    cube_arche.add_component<Shader_Component>();
    cube_arche.add_component<Mesh_Component>();
    cube_arche.add_component<Motion_Component>();
    core::Archetype_Manager::register_archetype(cube_arche, "cube_arche");

    core::Archetype text_arche;
    text_arche.add_component<Position_Component>();
    text_arche.add_component<Shader_Component>();
    text_arche.add_component<Static_Text_Component>();
    text_arche.add_component<Texture_Component>();
    core::Archetype_Manager::register_archetype(text_arche, "text_arche");

    core::Archetype dynam_arche;
    dynam_arche.add_component<Position_Component>();
    dynam_arche.add_component<Shader_Component>();
    dynam_arche.add_component<Dynamic_Text_Component>();
    dynam_arche.add_component<Texture_Component>();
    core::Archetype_Manager::register_archetype(dynam_arche, "dynam_arche");

    // Temp Vars
    Transform* transform;
    Mesh_Component* mesh_component;
    Shader_Component* mesh_shader_component;
    Motion_Component* motion_component;
    Position_Component* pos_component;

    float af = 5.0f;
    float vf = -4.0f;

    // Generate Cubes
    for (int p = 0; p < 5000; ++p) {
        core::Entity mesh_entity = core::Entity_Manager::create_entity("cube_arche");

        transform = core::Entity_Manager::get_component<Transform>(mesh_entity);
        transform->position = core::Vector3f(0, 0, 0);

        motion_component = core::Entity_Manager::get_component<Motion_Component>(mesh_entity);
        motion_component->acceleration = core::Vector3f(core::randf(-af, af), core::randf(-af, af), core::randf(-af, af));
        motion_component->velocity = motion_component->acceleration * vf;

        mesh_component = core::Entity_Manager::get_component<Mesh_Component>(mesh_entity);
        core::Asset_Manager::get_asset_handle("test_mesh", &mesh_component->mesh_handle);

        mesh_shader_component = core::Entity_Manager::get_component<Shader_Component>(mesh_entity);
        mesh_shader_component->program_id = mesh_shader_program;
    }

    // Create Controls Text
    core::Entity text_entity = core::Entity_Manager::create_entity("text_arche");

    std::string control_text = "Controls\n";
    control_text += "------------------------------------\n";
    control_text += "Forward = W | Backwards = S\n";
    control_text += "Up = Space | Down = X\n";
    control_text += "Rotate left = Q | Rotate Right = E\n";
    control_text += "Rotate Up = R | Rotate Down = F\n";
    control_text += "WireFrame On = T | WireFrame Off = Y\n";

    Shader_Component* text_shader_component;
    text_shader_component = core::Entity_Manager::get_component<Shader_Component>(text_entity);

    text_shader_component->program_id = text_shader_program;

    Font_Asset* font_asset = NULL;
    core::Asset_Manager::get_asset<Font_Asset>("arial", &font_asset);

    uint16_t text_size = 14;

    Static_Text_Component* static_text_component = core::Entity_Manager::get_component<Static_Text_Component>(text_entity);
    if (static_text_component == NULL) {
        LOG_ERROR("Error Finding static_text_component");
    }
    static_text_component->text = control_text;
    static_text_component->generate_static_text(control_text, text_size, &font_asset->font, 4);
    Texture_Component* texture_component;
    texture_component = core::Entity_Manager::get_component<Texture_Component>(text_entity);
    texture_component->texture_id = font_asset->font.get_font_texture_id(text_size);
    if ( texture_component->texture_id == 0 ) {
        LOG_ERROR("Could not get Texture")
    }

    pos_component = core::Entity_Manager::get_component<Position_Component>(text_entity);
    pos_component->position = core::Vector3f(25, 140, 0);

    // Dynamic Test
    text_entity = core::Entity_Manager::create_entity("dynam_arche");
    Engine::get_instance()->test_entity = text_entity;

    control_text = "Dynamic Test";

    text_shader_component = core::Entity_Manager::get_component<Shader_Component>(text_entity);

    text_shader_component->program_id = text_shader_program;

    core::Asset_Manager::get_asset<Font_Asset>("arial", &font_asset);

    text_size = 14;
    Dynamic_Text_Component* dynamic_text_component;
    dynamic_text_component = core::Entity_Manager::get_component<Dynamic_Text_Component>(text_entity);
    if (dynamic_text_component == NULL) {
        LOG_ERROR("Error Finding dynamic_text_component");
    }
    dynamic_text_component->string_font = &font_asset->font;
    dynamic_text_component->text = control_text;
    dynamic_text_component->size = text_size;
    dynamic_text_component->string_new_line_pad = 4;
    dynamic_text_component->generate_dynamic_text(control_text, text_size, &font_asset->font, 4);
    texture_component = core::Entity_Manager::get_component<Texture_Component>(text_entity);
    texture_component->texture_id = font_asset->font.get_font_texture_id(text_size);
    if ( texture_component->texture_id == 0 ) {
        LOG_ERROR("Could not get Texture")
    }

    pos_component = core::Entity_Manager::get_component<Position_Component>(text_entity);
    pos_component->position = core::Vector3f(15, 740, 0);
}
