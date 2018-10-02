#include "mesh_render_system.h"
#include "../asset_types/mesh_asset.h"
#include "../renderer.h"

Mesh_Render_System::Mesh_Render_System()
{
    name = "Mesh_Render_System";
    add_component<Position_Component>();
    add_component<Mesh_Component>();
    add_component<Shader_Component>();
}

void Mesh_Render_System::init()
{
    //glEnable(GL_POLYGON_SMOOTH);
    //glEnable(0x809D);
    glSwapIntervalEXT(0);
}

void Mesh_Render_System::update()
{
     render_command_t render_command;

     render_command.command_type = ENABLE_BLEND;
     render_command_queue.push_back(render_command);

     render_command.command_type = ENABLE_DEPTH_TEST;
     render_command_queue.push_back(render_command);

     render_command.command_type = ENABLE_CULL_FACE;
     render_command_queue.push_back(render_command);

     Position_Component* position_component;
     Shader_Component*   shader_component;
     Mesh_Component*     mesh_component;

     Mesh_Asset* mesh_asset = NULL;

     for(int i = 0; i < entity_count; i++) {

         position_component = get_data_at<Position_Component>(i);
         if ( position_component == NULL ) {
             LOG_ERROR("Mesh_Render_System: Failed to get Position_Component idx:" << i);
             continue;
         }

         shader_component = get_data_at<Shader_Component>(i);
         if ( shader_component == NULL ) {
             LOG_ERROR("Mesh_Render_System: Failed to get Shader_Component idx:" << i << " DATA " << (void*)shader_component);
             continue;
         }

         mesh_component = get_data_at<Mesh_Component>(i);
         if ( mesh_component == NULL ) {
             LOG_ERROR("Mesh_Render_System: Failed to get Mesh_Component idx:" << i);
             continue;
         }

         Engine::get_instance()->debug_camera->set_transformation(&position_component->position, 0, 0, 0, 1);
         render_command.command_type = RENDER_MESH;
         render_command.shader_id = shader_component->program_id;
         render_command.texture_id = 0;
         Engine::get_instance()->asset_manager->get_asset<Mesh_Asset>(mesh_component->mesh_handle, &mesh_asset);
         render_command.vao = mesh_asset->mesh.vao;
         render_command.indices_count = mesh_asset->mesh.indices_count;
         render_command.transformation_matrix = Engine::get_instance()->debug_camera->transformation_matrix;
         render_command_queue.push_back(render_command);
     }
}

void Mesh_Render_System::shutdown()
{

}
