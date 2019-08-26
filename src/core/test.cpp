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


     LOG("__id %d", test_shader.id());
     GLuint vertexbuffer;
     // Generate 1 buffer, put the resulting identifier in vertexbuffer
     Engine::OpenGL::glGenBuffers(1, &vertexbuffer);
     // The following commands will talk about our 'vertexbuffer' buffer
     Engine::OpenGL::glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
     // Give our vertices to OpenGL.
     Engine::OpenGL::glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
          Engine::OpenGL::glVertexAttribPointer(
                                                  0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                                                  3,                  // size
   GL_FLOAT,           // type
   GL_FALSE,           // normalized?
   3 *sizeof(float),                  // stride
   (void*)0            // array buffer offset
);
          Engine::OpenGL::glEnableVertexAttribArray(0);

     while( window.is_closed() == false ) {
          window.update();
          glViewport(0, 0, window.width(), window.height());
          glClearColor(0.5f, 0.6f, 0.7f, 1.0f);
          glClear(GL_COLOR_BUFFER_BIT);

          Engine::OpenGL::glUseProgram(test_shader.id());
          Engine::OpenGL::glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
// Draw the triangle !
          Engine::OpenGL::glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
          window.swap_buffers();
     }
}

