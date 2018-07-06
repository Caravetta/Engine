#include "dynamic_text_render_system.h"
#include "../renderer.h"

Dynamic_Text_Render_System::Dynamic_Text_Render_System()
{
    add_component(core::Component_Manager::get_instance()->id<Position_Component>());
    add_component(core::Component_Manager::get_instance()->id<Dynamic_Text_Component>());
    add_component(core::Component_Manager::get_instance()->id<Shader_Component>());
    add_component(core::Component_Manager::get_instance()->id<Texture_Component>());
}

void Dynamic_Text_Render_System::init()
{
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Dynamic_Text_Render_System::update()
{
    if ( entities->size() > 0 ) {
         core::Entity_Manager* enitiy_manager = Engine::get_instance()->enitiy_manager;
         core::Entity entity;

         Shader_Component shader_component;
         Position_Component pos_component;
         Static_Text_Component static_text_component;
         Texture_Component texture_component;

         render_command_t render_command;

         render_command.command_type = ENABLE_BLEND;
         render_command_queue.push_back(render_command);

         render_command.command_type = ENABLE_DEPTH_TEST;
         render_command_queue.push_back(render_command);

         render_command.command_type = DISABLE_CULL_FACE;
         render_command_queue.push_back(render_command);

         for (int i = 0; i < entities->size(); i++) {
              entity = entities->at(i);

              enitiy_manager->get_component<Position_Component>(entity, &pos_component);
              enitiy_manager->get_component<Shader_Component>(entity, &shader_component);
              enitiy_manager->get_component<Static_Text_Component>(entity, &static_text_component);
              enitiy_manager->get_component<Texture_Component>(entity, &texture_component);

              render_command.command_type = RENDER_TEXT;
              render_command.shader_id = shader_component.program_id;
              render_command.texture_id = texture_component.texture_id;
              render_command.vao = static_text_component.vao;
              render_command.indices_count = static_text_component.indices.size();
              render_command.position = pos_component.position;

              render_command_queue.push_back(render_command);
         }
    }
}

void Dynamic_Text_Render_System::shutdown()
{

}
