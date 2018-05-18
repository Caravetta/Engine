#include "mesh_render_system.h"
#include "../asset_types/mesh_asset.h"
#include "../renderer.h"

Mesh_Render_System::Mesh_Render_System()
{
    add_component(core::Component_Manager::get_instance()->id<Position_Component>());
    add_component(core::Component_Manager::get_instance()->id<Mesh_Component>());
    add_component(core::Component_Manager::get_instance()->id<Shader_Component>());
}

void Mesh_Render_System::init()
{
    //glEnable(GL_POLYGON_SMOOTH);
    //glEnable(0x809D);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    glSwapIntervalEXT(1);
}

void Mesh_Render_System::update()
{
    glViewport(0, 0, Engine::get_instance()->window->get_width(), Engine::get_instance()->window->get_height());
    glClearColor(0.16f, 0.29f, 0.48f, 0.54f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if ( entities->size() > 0 ) {
        core::Entity_Manager* enitiy_manager = Engine::get_instance()->enitiy_manager;
        core::Entity entity;
        Mesh_Asset* mesh_asset = NULL;
        Shader_Component shader_component;
        Mesh_Component mesh_component;
        Position_Component pos_component;
        Engine::get_instance()->debug_camera->set_view_matrix();

        render_command_t render_command;

        render_command.command_type = SET_PROJ_MATRIX;
        render_command.projection_matrix = Engine::get_instance()->debug_camera->projection_matrix;
        render_command_queue.push_back(render_command);

        render_command.command_type = SET_VIEW_MATRIX;
        render_command.projection_matrix = Engine::get_instance()->debug_camera->view_matrix;
        render_command_queue.push_back(render_command);

        for(int i = 0; i < entities->size(); i++) {

            entity = entities->at(i);
            enitiy_manager->get_component<Position_Component>(entity, &pos_component);
            enitiy_manager->get_component<Shader_Component>(entity, &shader_component);
            enitiy_manager->get_component<Mesh_Component>(entity, &mesh_component);

            Engine::get_instance()->debug_camera->set_transformation(&pos_component.position, 0, 0, 0, 1);
            render_command.command_type = RENDER_MESH;
            render_command.shader_id = shader_component.program_id;
            render_command.mesh_handle = mesh_component.mesh_handle;
            render_command.transformation_matrix = Engine::get_instance()->debug_camera->transformation_matrix;

            render_command_queue.push_back(render_command);
        }
    }
    render();
    Engine::get_instance()->window->swap_buffers();
}

void Mesh_Render_System::shutdown()
{

}
