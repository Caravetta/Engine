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
    START_TIME_BLOCK(mesh_render_System_update);
     render_command_t render_command;

     render_command.command_type = ENABLE_BLEND;
     render_command_queue.push_back(render_command);

     render_command.command_type = ENABLE_DEPTH_TEST;
     render_command_queue.push_back(render_command);

     render_command.command_type = ENABLE_CULL_FACE;
     render_command_queue.push_back(render_command);

     std::vector<Position_Component*>* position_vec = get_data_vec<Position_Component>();
     std::vector<Shader_Component*>* shader_vec = get_data_vec<Shader_Component>();
     std::vector<Mesh_Component*>* mesh_vec = get_data_vec<Mesh_Component>();



     Position_Component* position_component;
     Shader_Component*   shader_component;
     Mesh_Component*     mesh_component;

     Mesh_Asset* mesh_asset = NULL;

     for(int i = 0; i < entity_count; i++) {

         position_component = position_vec->at(i);
         shader_component = shader_vec->at(i);
         mesh_component = mesh_vec->at(i);

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
     END_TIME_BLOCK(mesh_render_System_update);
}

void Mesh_Render_System::shutdown()
{

}
