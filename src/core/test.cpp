#include "engine_core.h"
#include "glm.hpp"
#include "matrix_transform.hpp"
#include "matrix_clip_space.hpp"
#include <chrono>

#define WINDOW_WIDTH	800
#define WINDOW_HEIGHT	600

struct Transform {
     COMPONENT_DECLARE( Transform );

     Engine::Vector3f position;
};

COMPONENT_DEFINE( Transform );

struct Mesh_Handle {
     COMPONENT_DECLARE( Mesh_Handle );

     uint64_t handle;
};

COMPONENT_DEFINE( Mesh_Handle );


static const GLfloat g_vertex_buffer_data[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.5f,  0.5f, 0.0f,
     0.5f,  0.5f, 0.0f,
    -0.5f,  0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
};

int main(int argc, char** argv) {
     Engine::Rc_t rc = Engine::engine_init();
     if ( rc != Engine::SUCCESS ) {
          LOG_ERROR("Failed to init engine rc=%d", rc);
          return -1;
     }

     Engine::Window window(WINDOW_WIDTH, WINDOW_HEIGHT, "Test");

     Engine::Shader test_shader({{Engine::VERTEX_SHADER, "res/shader/chunk_vert_shader.glsl"},
                                 {Engine::FRAGMENT_SHADER, "res/shader/chunk_frag_shader.glsl"}});


     Engine::Entity entity = Engine::create_entity();

     Engine::add_components(entity, {Engine::component_id<Transform>(),
                                     Engine::component_id<Mesh_Handle>()});

     Engine::Entity_Group group({Engine::component_id<Transform>(),
                                 Engine::component_id<Mesh_Handle>()});

     Engine::Component_Data_Array<Mesh_Handle> mesh_handles(group);

     for ( size_t ii = 0; ii < mesh_handles.size(); ii++ ) {
          LOG("MESH idx %zd = %" PRIu64 "", ii, mesh_handles[ii].handle);
          mesh_handles[ii].handle = ii + 1000;
     }

     for ( size_t ii = 0; ii < mesh_handles.size(); ii++ ) {
          LOG("MESH idx %zd = %" PRIu64 "", ii, mesh_handles[ii].handle);
     }

     GLuint vertexArray_id;
     Engine::OpenGL::glGenVertexArrays(1, &vertexArray_id);
     Engine::OpenGL::glBindVertexArray(vertexArray_id);

     GLuint vertexbuffer;
     Engine::OpenGL::glGenBuffers(1, &vertexbuffer);
     Engine::OpenGL::glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
     Engine::OpenGL::glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
     Engine::OpenGL::glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
     Engine::OpenGL::glEnableVertexAttribArray(0);
     glClearColor(0.5f, 0.6f, 0.7f, 1.0f);

     //Engine::Matrix4f ortho = Engine::orthographic_projection(0, 600.0f, 0, 800.0f, -1, 1000);
     Engine::Matrix4f ortho = Engine::perspective_projection(Engine::radians(45), 800.0f/600.0f, 1.0f, 100.0f);

     float xx = 0;

     auto t_start = std::chrono::high_resolution_clock::now();

     while( window.is_closed() == false ) {
          window.update();
          glViewport(0, 0, window.width(), window.height());
          glClear(GL_COLOR_BUFFER_BIT);

          Engine::OpenGL::glUseProgram(test_shader.id());

          int32_t location = test_shader.uniform_id("color");
          test_shader.set_uniform_float3(location, 0.3f, 0, 0.3f);

          Engine::Matrix4f view = Engine::translate(Engine::Vector3f(0, 0, 0));

          Engine::Matrix4f model_trans = Engine::translate(Engine::Vector3f(0, 0, 50));
          Engine::Matrix4f model_scale = Engine::scale(Engine::Vector3f(10, 10, 0));

          auto t_now = std::chrono::high_resolution_clock::now();
          float time = std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_start).count();

          Engine::Matrix4f model_rot = Engine::rotation(Engine::Vector3f(60, 0, time*60));

          Engine::Matrix4f model = model_trans * model_rot * model_scale;

          Engine::Matrix4f mvp = ortho * view * model;

          location = test_shader.uniform_id("mvp");
          test_shader.set_uniform_mat4(location, (Engine::Matrix4f*)&mvp);

          Engine::OpenGL::glEnableVertexAttribArray(0);
          Engine::OpenGL::glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
          Engine::OpenGL::glDrawArrays(GL_TRIANGLES, 0, 6);

          window.swap_buffers();
     }
}

