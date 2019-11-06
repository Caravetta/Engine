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

char pass_vert[] = "                                                                 \
               #version 330 core\n                                                   \
                                                                                     \
               layout(location = 0) in vec3 vertexPosition_modelspace;\n             \
                                                                                     \
               out vec2 uv;\n                                                        \
                                                                                     \
               void main(){\n                                                        \
                    gl_Position = vec4(vertexPosition_modelspace, 1);\n              \
                    uv = (vertexPosition_modelspace.xy+vec2(1,1))/2.0;\n             \
               }\n                                                                   \
              ";


char pass_frag1[] = "                                        \
               #version 330 core\n                          \
                out vec4 color;\n                       \
                in vec2 uv;\n                               \
                                                            \
               uniform sampler2D text;\n                     \
			mat3 sx = mat3( 1.0, 2.0, 1.0, 0.0, 0.0, 0.0, -1.0, -2.0, -1.0 );\n\
			mat3 sy = mat3( 1.0, 0.0, -1.0, 2.0, 0.0, -2.0, 1.0, 0.0, -1.0 );\n\
               void main()\n                                \
               {\n                                          \
			  vec3 diffuse = texture(text, uv.st).rgb;\n\
    		       mat3 I;\n\
    			  for (int i=0; i<3; i++) {\n\
        			for (int j=0; j<3; j++) {\n\
            			vec3 sample  = texelFetch(text, ivec2(gl_FragCoord) + ivec2(i-1,j-1), 0 ).rgb;\n\
            			I[i][j] = length(sample);\n\
				}\n\
    			  }\n\
			  float gx = dot(sx[0], I[0]) + dot(sx[1], I[1]) + dot(sx[2], I[2]);\n\
			  float gy = dot(sy[0], I[0]) + dot(sy[1], I[1]) + dot(sy[2], I[2]);\n\
		       float g = sqrt(pow(gx, 2.0)+pow(gy, 2.0));\n\
			  color = vec4(diffuse - vec3(g), 1.0);\n\
               }\n                                          \
              ";

float RandomFloat(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

float vertices[] = {
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left
};
unsigned int indices[] = {
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
};

struct Outline_Pass : public Engine::Render_Pass {
     Engine::Render_Texture* _outline;
     Engine::Material* _material;

     Outline_Pass( Engine::Material& material )
     {
          _material = &material;
     };

     void configure( void )
     {
          Engine::Render_Texture_Info texture_info(WINDOW_WIDTH, WINDOW_HEIGHT, Engine::Texture_Format::RGB_FORMAT);
          _outline = new (std::nothrow) Engine::Render_Texture(texture_info);
     };

     void execute( Engine::Render_Context& context )
     {
          blit(context, context.cur_color_texture(), *_outline, *_material);
     };

     void cleanup( void )
     {
     };
};

int main(int argc, char** argv) {

     Engine::Rc_t rc = Engine::engine_init();
     if ( rc != Engine::SUCCESS ) {
          LOG_ERROR("Failed to init engine rc=%d", rc);
          return -1;
     }

     Engine::Window window(WINDOW_WIDTH, WINDOW_HEIGHT, "Test");
     Engine::Window window1(WINDOW_WIDTH, WINDOW_HEIGHT, "Test1");

     std::vector<Engine::Shader_String> shader_strings = {{Engine::VERTEX_SHADER, vert, sizeof(vert)},
                                                          {Engine::FRAGMENT_SHADER, frag, sizeof(frag)}};

     Engine::Shader test_shader(shader_strings);

     std::vector<Engine::Shader_String> pass1_shader_strings = {{Engine::VERTEX_SHADER, pass_vert, sizeof(pass_vert)},
                                                               {Engine::FRAGMENT_SHADER, pass_frag1, sizeof(pass_frag1)}};

     Engine::Shader pass1_shader(pass1_shader_strings);

     Engine::Mesh_Data mesh_data;
     mesh_data.positions.resize(12);
     memcpy(mesh_data.positions.data(), vertices, sizeof(vertices));
     mesh_data.indices.resize(6);
     memcpy(mesh_data.indices.data(), indices, sizeof(indices));
     Engine::load_mesh(Engine::STATIC_MESH, "Test_Mesh", mesh_data);

     Engine::Mesh_Handle mesh_handle = Engine::mesh_handle("Test_Mesh");

     uint32_t square_vertexArray_id = Engine::create_vertex_array();
     Engine::bind_vertex_array(square_vertexArray_id);

     uint32_t square_inc_vertexbuffer_id = Engine::create_vertex_buffer();
     Engine::bind_vertex_buffer(Engine::Buffer_Type::ELEMENT_ARRAY_BUFFER, square_inc_vertexbuffer_id);
     Engine::buffer_vertex_data(Engine::Buffer_Type::ELEMENT_ARRAY_BUFFER, (uint8_t*)indices, sizeof(indices), Engine::STATIC_DRAW);
     Engine::bind_vertex_buffer(Engine::Buffer_Type::ELEMENT_ARRAY_BUFFER, 0);

     uint32_t square_vertexbuffer_id = Engine::create_vertex_buffer();
     Engine::bind_vertex_buffer(Engine::Buffer_Type::ARRAY_BUFFER, square_vertexbuffer_id);
     Engine::buffer_vertex_data(Engine::Buffer_Type::ARRAY_BUFFER, (uint8_t*)vertices, sizeof(vertices), Engine::STATIC_DRAW);
     Engine::enable_vertex_attrib(0);
     Engine::define_vertex_attrib(0, 3, false, Engine::FLOAT_DATA, 3 * sizeof(float), 0);
     Engine::bind_vertex_buffer(Engine::Buffer_Type::ARRAY_BUFFER, 0);

     Engine::bind_vertex_array(0);

     Engine::Matrix4f ortho = Engine::perspective_projection(Engine::radians(45),
                                                             (float)window.width()/(float)window.height(),
                                                             1.0f,
                                                             100.0f);

     auto t_start = std::chrono::high_resolution_clock::now();

     Engine::enable_graphics_option(Engine::DEPTH_TEST_OPTION);
     Engine::set_depth_func(Engine::DEPTH_LESS_FUNC);

     Engine::set_clear_color(0.5f, 0.6f, 0.7f, 1.0f);
     int32_t color_location = test_shader.uniform_id("color");
     int32_t mvp_location = test_shader.uniform_id("mvp");

     Engine::set_clear_color(0.5f, 0.6f, 0.7f, 1.0f);

     #define ENTS 10

     std::vector<Engine::Entity> entities;

     for ( size_t ii = 0; ii < ENTS; ii++ ) {
          Engine::Entity entity = Engine::create_entity();
          entities.push_back(entity);

          Engine::add_components(entity, {Engine::component_id<Engine::Transform>(),
                                          Engine::component_id<Engine::Mesh_Info>()});

          Engine::Transform* transform = Engine::get_component<Engine::Transform>(entity);

          transform->position = Engine::Vector3f(RandomFloat(-2, 2), RandomFloat(-2, 2), RandomFloat(4, 10));
          transform->scale = Engine::Vector3f(0.1f, 0.1f, 0.0f);
          transform->rotation = Engine::Vector3f(70, 0, 0);
     }

     Engine::Vector3f cam_pos(0, 0, 0);
     Engine::Vector3f cam_rot(0, 0, 0);

     Engine::Render_Texture_Info texture_info(WINDOW_WIDTH, WINDOW_HEIGHT, Engine::Texture_Format::RGB_FORMAT);

     Engine::Render_Texture base(texture_info);

     Engine::Render_Context render_context;
     render_context.init();

     Engine::Material outline_material(pass1_shader);
     Outline_Pass outline_pass(outline_material);

     outline_pass.configure();

     Engine::Timer frame_time;

     frame_time.start();

     while( window.is_closed() == false && window1.is_closed() == false ) {
          frame_time.start();
          window.update();
          window1.update();

          Engine::enable_graphics_option(Engine::DEPTH_TEST_OPTION);
          Engine::set_depth_func(Engine::DEPTH_LESS_FUNC);

          render_context.bind();
          render_context.set_color_texture(base);

          Engine::set_view_port(0, 0, window.width(), window.height());

          Engine::graphics_clear(Engine::COLOR_BUFFER_CLEAR | Engine::DEPTH_BUFFER_CLEAR);

          Engine::use_program(test_shader.id());

          test_shader.set_uniform_float3(color_location, 0.3f, 0, 0.3f);

          if ( Engine::is_key_pressed(Engine::W_KEY) ) {
               cam_pos.z -= 0.1f;
          } else if ( Engine::is_key_pressed(Engine::S_KEY) ) {
               cam_pos.z += 0.1f;
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

          Engine::Entity_Group group({Engine::component_id<Engine::Mesh_Info>(),
                                      Engine::component_id<Engine::Transform>()});

          Engine::Component_Data_Array<Engine::Transform> trans_infos(group);

          Engine::bind_vertex_array(square_vertexArray_id);
          Engine::bind_vertex_buffer(Engine::Buffer_Type::ELEMENT_ARRAY_BUFFER, square_inc_vertexbuffer_id);

          for ( size_t ii = 0; ii < entities.size(); ii++ ) {
               Engine::Transform& trans = trans_infos[ii];
               Engine::Transform* transform_p = Engine::get_component<Engine::Transform>(entities[ii]);

               if ( transform_p != &trans ) {
                    LOG("transform_p:%p trans:%p", transform_p, &trans);
               }

               trans.rotation = Engine::Vector3f(time*30, time*20, time*40);
               Engine::Matrix4f model_transform = Engine::model_transform(trans.position,
                                                                          trans.scale,
                                                                          trans.rotation);

               Engine::Matrix4f mvp = ortho * view_transform * model_transform;
               test_shader.set_uniform_mat4(mvp_location, (Engine::Matrix4f*)&mvp);

               Engine::draw_elements_data(Engine::TRIANGLE_MODE, 6, Engine::UNSIGNED_INT, 0);
          }

          outline_pass.execute(render_context);
          render_context.bit_to_screen();
          window.swap_buffers();
          window1.swap_buffers();
          float dt = (float)frame_time.elapsed_milli_sec();
          LOG("DT %fms", dt);
     }
}

