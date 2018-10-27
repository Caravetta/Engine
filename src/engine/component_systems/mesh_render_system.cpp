#include "mesh_render_system.h"
#include "../asset_types/mesh_asset.h"
#include "../renderer.h"

Mesh_Render_System::Mesh_Render_System()
{
    name = "Mesh_Render_System";
    add_component<Transform>();
    add_component<Mesh_Component>();
    add_component<Shader_Component>();
}

void Mesh_Render_System::init()
{
    //glEnable(GL_POLYGON_SMOOTH);
    //glEnable(0x809D);
    glSwapIntervalEXT(0);
}

#define PI 3.14159265

float _to_radians( float angle ) //TODO: need to move this into math lib
{
    return (float)((angle * PI) / 180);
}

core::Vector3f vec_x(1, 0, 0);
core::Vector3f vec_y(0, 1, 0);
core::Vector3f vec_z(0, 0, 1);

struct __declspec(align(16)) math_job : public core::Job_Loop {
    std::vector<render_command_t>* commands;
    std::vector<Transform*>* transforms;

    void Execute( uint64_t index ) {
        Transform* transform = transforms->at(index);

        render_command_t*   render_command = &commands->at(index);
        render_command->transformation_matrix.identity();
        render_command->transformation_matrix.translate(&transform->position);
        render_command->transformation_matrix.scale(1);
    }
};

struct __declspec(align(16)) mesh_render_job : public core::Job_Loop {
    std::vector<Transform*>* position_vec;
    std::vector<Shader_Component*>* shader_vec;
    std::vector<Mesh_Component*>* mesh_vec;
    std::vector<render_command_t>* commands;
    std::vector<core::Matrix4f>* mats;
    Engine* engine;

    void Execute( uint64_t index ) {
        render_command_t*   render_command = &commands->at(index);
        Transform* position_component = position_vec->at(index);
        Shader_Component*   shader_component = shader_vec->at(index);
        Mesh_Component*     mesh_component = mesh_vec->at(index);
        Mesh_Asset*         mesh_asset = NULL;

        render_command->command_type = RENDER_MESH;
        render_command->shader_id = shader_component->program_id;
        render_command->texture_id = 0;
        core::Asset_Manager::get_asset_with_handle<Mesh_Asset>(mesh_component->mesh_handle, &mesh_asset);
        render_command->vao = mesh_asset->mesh.vao;
        render_command->indices_count = mesh_asset->mesh.indices_count;
    }
};

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

     Engine* engine = Engine::get_instance();

#if 1
     std::vector<Transform*>* transforms = get_data_vec<Transform>();
     std::vector<Shader_Component*>* shader_vec = get_data_vec<Shader_Component>();
     std::vector<Mesh_Component*>* mesh_vec = get_data_vec<Mesh_Component>();

     Transform* transform;
     Shader_Component*   shader_component;
     Mesh_Component*     mesh_component;

     Mesh_Asset* mesh_asset = NULL;

     for(int i = 0; i < entity_count; i++) {
         transform = transforms->at(i);
         shader_component = shader_vec->at(i);
         mesh_component = mesh_vec->at(i);
        //START_TIME_BLOCK(mesh_render_System_math);
        core::Matrix4f transformation_matrix;
        transformation_matrix.identity();
        transformation_matrix.translate(&transform->position);
        //transformation_matrix.rotate(_to_radians(0), &vec_x);
        //transformation_matrix.rotate(_to_radians(0), &vec_y);
        //transformation_matrix.rotate(_to_radians(0), &vec_z);
        transformation_matrix.scale(1);
        //END_TIME_BLOCK(mesh_render_System_math);

        render_command.transformation_matrix = transformation_matrix;

         //engine->debug_camera->set_transformation(&position_component->position, 0, 0, 0, 1);
         render_command.command_type = RENDER_MESH;
         render_command.shader_id = shader_component->program_id;
         render_command.texture_id = 0;
         core::Asset_Manager::get_asset_with_handle<Mesh_Asset>(mesh_component->mesh_handle, &mesh_asset);
         render_command.vao = mesh_asset->mesh.vao;
         render_command.indices_count = mesh_asset->mesh.indices_count;
         //render_command.transformation_matrix = Engine::get_instance()->debug_camera->transformation_matrix;
         render_command_queue.push_back(render_command);
     }
#endif
#if 0
    core::Job_Manager* job_manager = core::Job_Manager::get_instance();
    std::vector<render_command_t> commands;
    commands.resize(entity_count);

     math_job math_jober;
     math_jober.position_vec = get_data_vec<Position_Component>();
     math_jober.commands = &commands;
     core::Job_Handle job_handle1 = math_jober.Schedule(entity_count, 1000);
     while (job_manager->is_job_complete(job_handle1) == false) {};

     mesh_render_job job;
     job.position_vec = get_data_vec<Position_Component>();
     job.shader_vec = get_data_vec<Shader_Component>();
     job.mesh_vec = get_data_vec<Mesh_Component>();
     job.engine = engine;
     job.commands = &commands;//.resize(entity_count);
     core::Job_Handle job_handle = job.Schedule(entity_count, 1000);
     while (job_manager->is_job_complete(job_handle) == false) {};
     //START_TIME_BLOCK(mesh_render_System_loop);
     for (uint64_t ii = 0; ii < commands.size(); ii++) {
        render_command_queue.push_back(commands[ii]);
     }
     //END_TIME_BLOCK(mesh_render_System_loop);
#endif
     END_TIME_BLOCK(mesh_render_System_update);
}

void Mesh_Render_System::shutdown()
{

}
