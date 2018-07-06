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
    glSwapIntervalEXT(1);
}

void Mesh_Render_System::update()
{
    if ( entities->size() > 0 ) {
        core::Entity_Manager* enitiy_manager = Engine::get_instance()->enitiy_manager;
        core::Entity entity;
        Mesh_Asset* mesh_asset = NULL;
        Shader_Component shader_component;
        Mesh_Component mesh_component;
        Position_Component pos_component;

        render_command_t render_command;

        render_command.command_type = ENABLE_BLEND;
        render_command_queue.push_back(render_command);

        render_command.command_type = ENABLE_DEPTH_TEST;
        render_command_queue.push_back(render_command);

        render_command.command_type = ENABLE_CULL_FACE;
        render_command_queue.push_back(render_command);

        for(int i = 0; i < entities->size(); i++) {
            entity = entities->at(i);
            enitiy_manager->get_component<Position_Component>(entity, &pos_component);
            enitiy_manager->get_component<Shader_Component>(entity, &shader_component);
            enitiy_manager->get_component<Mesh_Component>(entity, &mesh_component);

            Engine::get_instance()->debug_camera->set_transformation(&pos_component.position, 0, 0, 0, 1);
            render_command.command_type = RENDER_MESH;
            render_command.shader_id = shader_component.program_id;
            render_command.texture_id = 0;
            Engine::get_instance()->asset_manager->get_asset<Mesh_Asset>(mesh_component.mesh_handle, &mesh_asset);
            render_command.vao = mesh_asset->mesh.vao;
            render_command.indices_count = mesh_asset->mesh.indices_count;
            render_command.transformation_matrix = Engine::get_instance()->debug_camera->transformation_matrix;

            render_command_queue.push_back(render_command);
        }
    }
}

void Mesh_Render_System::shutdown()
{

}
