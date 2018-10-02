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


        position_component = get_data_at<Position_Component>(i);
        if ( position_component == NULL ) {
            LOG_ERROR("Text_Render_System: Failed to get Position_Component idx:" << i);
            continue;
        }

        shader_component = get_data_at<Shader_Component>(i);
        if ( shader_component == NULL ) {
            LOG_ERROR("Text_Render_System: Failed to get Shader_Component idx:" << i);
            continue;
        }

        static_text_component = get_data_at<Static_Text_Component>(i);
        if ( static_text_component == NULL ) {
            LOG_ERROR("Text_Render_System: Failed to get Static_Text_Component idx:" << i);
            continue;
        }

        texture_component = get_data_at<Texture_Component>(i);
        if ( texture_component == NULL ) {
            LOG_ERROR("Text_Render_System: Failed to get Texture_Component idx:" << i);
            continue;
        }

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
