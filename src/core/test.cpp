#include "engine_core.h"

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
   -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    0.0f,  1.0f, 0.0f,
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

     while( window.is_closed() == false ) {
          window.update();
          glViewport(0, 0, window.width(), window.height());
          glClear(GL_COLOR_BUFFER_BIT);

          Engine::OpenGL::glUseProgram(test_shader.id());
          Engine::OpenGL::glEnableVertexAttribArray(0);
          Engine::OpenGL::glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
          Engine::OpenGL::glDrawArrays(GL_TRIANGLES, 0, 3);

          window.swap_buffers();
     }
}

