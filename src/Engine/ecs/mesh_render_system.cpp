#include "Engine.h"
#include "renderer.h"
#include "mesh_manager.h"
#include "texture_manager.h"
#include "math_utils.h"
#include "material_manager.h"

namespace Engine {

Mesh_Render_System::Mesh_Render_System()
{
    add_component(TRANSFORM_COMP);
    add_component(MESH_HANDLE_COMP);
    add_component(MATERIAL_HANDLE_COMP);
}

void Mesh_Render_System::init()
{
    //glEnable(GL_POLYGON_SMOOTH);
    //glEnable(0x809D);
    //glSwapIntervalEXT(0);
}

void Mesh_Render_System::update()
{
    render_command_t render_command;

    render_command.command_type = ENABLE_BLEND;
    enqueue_render_command(render_command);

    render_command.command_type = ENABLE_DEPTH_TEST;
    enqueue_render_command(render_command);

    //render_command.command_type = ENABLE_CULL_FACE;
    render_command.command_type = DISABLE_CULL_FACE;
    enqueue_render_command(render_command);

    std::vector<Transform*>* transforms = (std::vector<Transform*>*)get_data_vec(TRANSFORM_COMP);
    std::vector<Mesh_Handle*>* mesh_vec = (std::vector<Mesh_Handle*>*)get_data_vec(MESH_HANDLE_COMP);
    std::vector<Material_Handle*>* material_vec = (std::vector<Material_Handle*>*)get_data_vec(MATERIAL_HANDLE_COMP);

    Transform* transform;
    Mesh_Handle* mesh_handle;
    Material_Handle* material_handle;

    for( u64 i = 0; i < entity_count; i++ ) {

        transform = transforms->at(i);
        mesh_handle = mesh_vec->at(i);
        material_handle = material_vec->at(i);

        // Calculate the entity's transform matrix
        Engine::Matrix4f base;
        base.identity();
        Engine::Matrix4f translate_matrix = Engine::translate(base, transform->position);
        Engine::Matrix4f scale_matrix = Engine::scale(base, transform->scale);
        render_command.transformation_matrix = scale_matrix * translate_matrix;

        render_command.command_type = RENDER_MESH;
        render_command.material_handle = *material_handle;
        render_command.mesh_handle = *mesh_handle;

        enqueue_render_command(render_command);
    }
}

void Mesh_Render_System::shutdown()
{

}

} // end namespace Engine
