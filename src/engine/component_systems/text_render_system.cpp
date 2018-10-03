#include "text_render_system.h"
#include "../renderer.h"

Text_Render_System::Text_Render_System()
{
    name = "Text_Render_System";
    add_component(core::Component_Manager::get_instance()->id<Position_Component>());
    add_component(core::Component_Manager::get_instance()->id<Static_Text_Component>());
    add_component(core::Component_Manager::get_instance()->id<Shader_Component>());
    add_component(core::Component_Manager::get_instance()->id<Texture_Component>());
}

void Text_Render_System::init()
{
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Text_Render_System::update()
{
    std::vector<Position_Component*>* position_vec = get_data_vec<Position_Component>();
    std::vector<Shader_Component*>* shader_vec = get_data_vec<Shader_Component>();
    std::vector<Static_Text_Component*>* static_text_vec = get_data_vec<Static_Text_Component>();
    std::vector<Texture_Component*>* texture_vec = get_data_vec<Texture_Component>();

    Position_Component* position_component;
    Shader_Component*   shader_component;
    Static_Text_Component* static_text_component;
    Texture_Component* texture_component;

    render_command_t render_command;

    render_command.command_type = ENABLE_BLEND;
    render_command_queue.push_back(render_command);

    render_command.command_type = ENABLE_DEPTH_TEST;
    render_command_queue.push_back(render_command);

    render_command.command_type = DISABLE_CULL_FACE;
    render_command_queue.push_back(render_command);

    for(int i = 0; i < entity_count; i++) {

        position_component = position_vec->at(i);
        shader_component = shader_vec->at(i);
        static_text_component = static_text_vec->at(i);
        texture_component = texture_vec->at(i);

        render_command.command_type = RENDER_TEXT;
        render_command.shader_id = shader_component->program_id;
        render_command.texture_id = texture_component->texture_id;
        render_command.vao = static_text_component->vao;
        render_command.indices_count = (uint32_t)static_text_component->indices->size();
        render_command.position = position_component->position;

        render_command_queue.push_back(render_command);
    }
}

void Text_Render_System::shutdown()
{

}
