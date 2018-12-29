#include "Engine.h"
#include "renderer.h"
#include "mesh_manager.h"
#include "math_utils.h"

namespace Engine {

Mesh_Render_System::Mesh_Render_System()
{
    add_component(TRANSFORM_COMP);
    add_component(MESH_HANDLE_COMP);
    add_component(SHADER_ID_COMP);
}

void Mesh_Render_System::init()
{
    //glEnable(GL_POLYGON_SMOOTH);
    //glEnable(0x809D);
    //glSwapIntervalEXT(0);
}

Vector3f vec_x(1, 0, 0);
Vector3f vec_y(0, 1, 0);
Vector3f vec_z(0, 0, 1);

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
    std::vector<Shader_ID*>* shader_vec = (std::vector<Shader_ID*>*)get_data_vec(SHADER_ID_COMP);
    std::vector<Mesh_Handle*>* mesh_vec = (std::vector<Mesh_Handle*>*)get_data_vec(MESH_HANDLE_COMP);

    Transform* transform;
    Shader_ID* shader_component;
    Mesh_Handle* mesh_component;

    for( u64 i = 0; i < entity_count; i++ ) {
        transform = transforms->at(i);
        shader_component = shader_vec->at(i);
        mesh_component = mesh_vec->at(i);
        Matrix4f transformation_matrix;
        transformation_matrix.identity();
        transformation_matrix.translate(&transform->position);
        transformation_matrix.rotate(to_radians(transform->rotation.x), &vec_x);
        transformation_matrix.rotate(to_radians(transform->rotation.y), &vec_y);
        transformation_matrix.rotate(to_radians(transform->rotation.z), &vec_z);
        transformation_matrix.scale(transform->scale.x);
#if 0
        LOG("Current:");
        LOG(transformation_matrix);

        Matrix4f test;
        test.identity();
        test = test.generate_transform(Vector3f(0.5, 0.5, 0.5), transform->position);
        LOG("TEST:");
        LOG(test);

        if ( i == 0 ) {
        render_command.transformation_matrix = test;
        } else {
        render_command.transformation_matrix = test;
        }
#endif
        render_command.transformation_matrix = transformation_matrix;

        render_command.command_type = RENDER_MESH;
        render_command.shader_id = shader_component->program_id;
        render_command.texture_id = 0;
        render_command.vao = Mesh_Manager::get_mesh_vao(*mesh_component);
        render_command.indices_count = Mesh_Manager::get_indices_count(*mesh_component);
        enqueue_render_command(render_command);
    }
}

void Mesh_Render_System::shutdown()
{

}

} // end namespace Engine
