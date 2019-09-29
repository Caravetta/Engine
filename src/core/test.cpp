#include "engine_core.h"
#if 0
#include "glm.hpp"
#include "matrix_transform.hpp"
#include "matrix_clip_space.hpp"
#endif
#include <chrono>

#define WINDOW_WIDTH	800
#define WINDOW_HEIGHT	600

char vert[] = "                                                                      \
               #version 330 core\n                                                   \
                                                                                     \
               layout(location = 0) in vec3 vertexPosition_modelspace;\n             \
                                                                                     \
               uniform mat4 mvp;\n                                                   \
                                                                                     \
               void main(){\n                                                        \
                    vec4 pos = mvp * vec4(vertexPosition_modelspace, 1);\n           \
                    gl_Position = pos;\n                                             \
               }\n                                                                   \
              ";

char frag[] = "                           \
               #version 330 core\n        \
                out vec3 color_out;\n      \
                                          \
               uniform vec3 color;\n      \
               void main()\n              \
               {\n                        \
                   color_out = color;\n  \
               }\n                        \
              ";

struct Mesh_Handle {
     COMPONENT_DECLARE( Mesh_Handle );

     uint64_t handle;
};

COMPONENT_DEFINE( Mesh_Handle );

float RandomFloat(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

static const float g_vertex_buffer_data[] = {
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

     std::vector<Engine::Shader_String> shader_strings = {{Engine::VERTEX_SHADER, vert, sizeof(vert)},
                                                          {Engine::FRAGMENT_SHADER, frag, sizeof(frag)}};

     Engine::Shader test_shader(shader_strings);

     Engine::Entity entity = Engine::create_entity();

     Engine::add_components(entity, {Engine::component_id<Engine::Transform>(),
                                     Engine::component_id<Mesh_Handle>()});

     Engine::Entity_Group group({Engine::component_id<Engine::Transform>(),
                                 Engine::component_id<Mesh_Handle>()});

     Engine::Component_Data_Array<Mesh_Handle> mesh_handles(group);

     for ( size_t ii = 0; ii < mesh_handles.size(); ii++ ) {
          LOG("MESH idx %zd = %" PRIu64 "", ii, mesh_handles[ii].handle);
          mesh_handles[ii].handle = ii + 1000;
     }

     for ( size_t ii = 0; ii < mesh_handles.size(); ii++ ) {
          LOG("MESH idx %zd = %" PRIu64 "", ii, mesh_handles[ii].handle);
     }

     uint32_t vertexArray_id = Engine::create_vertex_array();
     Engine::bind_vertex_array(vertexArray_id);

     uint32_t vertexbuffer_id = Engine::create_vertex_buffer();
     Engine::bind_vertex_buffer(vertexbuffer_id);
     Engine::buffer_vertex_data((uint8_t*)g_vertex_buffer_data, sizeof(g_vertex_buffer_data));
     Engine::define_vertex_attrib(0, 3, Engine::FLOAT_DATA, 3 * sizeof(float), 0);
     Engine::enable_vertex_attrib(0);

     uint32_t vertexbuffer_id1 = Engine::create_vertex_buffer();
     Engine::bind_vertex_buffer(vertexbuffer_id);
     Engine::buffer_vertex_data((uint8_t*)g_vertex_buffer_data, sizeof(g_vertex_buffer_data));
     Engine::define_vertex_attrib(0, 3, Engine::FLOAT_DATA, 3 * sizeof(float), 0);
     Engine::enable_vertex_attrib(0);
     Engine::Matrix4f ortho = Engine::perspective_projection(Engine::radians(45),
                                                             (float)window.width()/(float)window.height(),
                                                             1.0f,
                                                             100.0f);

     auto t_start = std::chrono::high_resolution_clock::now();

     Engine::enable_graphics_option(Engine::DEPTH_TEST);
     Engine::set_depth_func(Engine::DEPTH_LESS_FUNC);

     Engine::set_clear_color(0.5f, 0.6f, 0.7f, 1.0f);
     int32_t color_location = test_shader.uniform_id("color");
     int32_t mvp_location = test_shader.uniform_id("mvp");

     //Engine::Fbo_Handle fbo = Engine::create_fbo( true );
     //LOG("JOSH FBO IN TEST %" PRIu64 "", fbo);
     Engine::set_clear_color(0.5f, 0.6f, 0.7f, 1.0f);

     #define ENTS 10

     Engine::Transform transforms[ENTS];

     for ( size_t ii = 0; ii < ENTS; ii++ ) {
          transforms[ii].position = Engine::Vector3f(RandomFloat(-2, 2), RandomFloat(-2, 2), RandomFloat(4, 10));
          transforms[ii].scale = Engine::Vector3f(0.1, 0.1, 0);
          transforms[ii].rotation = Engine::Vector3f(70, 0, 0);
     }

     Engine::Vector3f cam_pos(0, 0, 0);
     Engine::Vector3f cam_rot(0, 0, 0);

     while( window.is_closed() == false ) {
          window.update();
          //Engine::bind_fbo(fbo);
          Engine::set_view_port(0, 0, window.width(), window.height());
          Engine::graphics_clear(Engine::COLOR_BUFFER_CLEAR | Engine::DEPTH_BUFFER_CLEAR);

          Engine::use_program(test_shader.id());

          test_shader.set_uniform_float3(color_location, 0.3f, 0, 0.3f);

          if ( Engine::is_key_pressed(Engine::W_KEY) ) {
               cam_pos.z -= 0.1;
          } else if ( Engine::is_key_pressed(Engine::S_KEY) ) {
               cam_pos.z += 0.1;
          }

          if ( Engine::is_key_pressed(Engine::A_KEY) ) {
               cam_rot.y += 1;
          } else if ( Engine::is_key_pressed(Engine::D_KEY) ) {
               cam_rot.y -= 1;
          }

          Engine::Matrix4f view_transform = Engine::view_transform(cam_pos,
                                                                   Engine::Vector3f(0, 0, 0),
                                                                   cam_rot);

          auto t_now = std::chrono::high_resolution_clock::now();
          float time = std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_start).count();

          //Engine::use_program(-1);

          for ( size_t ii = 0; ii < ENTS; ii++ ) {
               //transforms[ii].rotation = Engine::Vector3f(time*30, time*20, time*40);
               Engine::Matrix4f model_transform = Engine::model_transform(transforms[ii].position,
                                                                          transforms[ii].scale,
                                                                          transforms[ii].rotation);

               Engine::Matrix4f mvp = ortho * view_transform * model_transform;
               test_shader.set_uniform_mat4(mvp_location, (Engine::Matrix4f*)&mvp);
               Engine::enable_vertex_attrib(0);
               Engine::bind_vertex_buffer(vertexbuffer_id);
               Engine::draw_data(Engine::TRIANGLE_MODE, 0, 6);
          }
#if 0
          Engine::use_program(-2);
          Engine::use_program(test_shader.id());

          test_shader.set_uniform_float3(color_location, 0.3f, 0, 0.3f);

          for ( size_t ii = 0; ii < ENTS; ii++ ) {
               //transforms[ii].rotation = Engine::Vector3f(time*30, time*20, time*40);
               Engine::Matrix4f model_transform = Engine::model_transform(transforms[ii].position,
                                                                          transforms[ii].scale,
                                                                          transforms[ii].rotation);

               Engine::Matrix4f mvp = ortho * view_transform * model_transform;
               test_shader.set_uniform_mat4(mvp_location, (Engine::Matrix4f*)&mvp);
               Engine::enable_vertex_attrib(0);
               Engine::bind_vertex_buffer(vertexbuffer_id);
               Engine::draw_data(Engine::TRIANGLE_MODE, 0, 6);
          }
#endif
          window.swap_buffers();
     }
}

