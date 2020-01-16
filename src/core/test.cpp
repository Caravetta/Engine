#include "engine_core.h"
#include "basic_renderer.h"
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
          Engine::Render_Texture_Info texture_info(WINDOW_WIDTH, WINDOW_HEIGHT, Engine::Texture_Format::RGB_FORMAT, Engine::Data_Type::UNSIGNED_BYTE);
          _outline = new (std::nothrow) Engine::Render_Texture(texture_info);
     };

     void execute( Engine::Render_Context& context )
     {
          blit(context, *context.get_color_texture(Engine::Attachment_Type::COLOR_ATTACHMENT_0), *_outline, *_material);
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

     Engine::register_system<Engine::Basic_Renderer>();

     Engine::Window window(WINDOW_WIDTH, WINDOW_HEIGHT, "Test");

     Engine::init_systems();

     std::vector<Engine::Shader_String> shader_strings = {{Engine::VERTEX_SHADER, vert, sizeof(vert)},
                                                          {Engine::FRAGMENT_SHADER, frag, sizeof(frag)}};

     Engine::Shader test_shader(shader_strings);

     Engine::add_shader(test_shader.id(), test_shader);

     std::vector<Engine::Shader_String> pass1_shader_strings = {{Engine::VERTEX_SHADER, pass_vert, sizeof(pass_vert)},
                                                               {Engine::FRAGMENT_SHADER, pass_frag1, sizeof(pass_frag1)}};

     Engine::Shader pass1_shader(pass1_shader_strings);
     Engine::add_shader(pass1_shader.id(), pass1_shader);

     Engine::Mesh_Data mesh_data;
     mesh_data.positions.resize(12);
     memcpy(mesh_data.positions.data(), vertices, sizeof(vertices));
     mesh_data.indices.resize(6);
     memcpy(mesh_data.indices.data(), indices, sizeof(indices));
     Engine::load_mesh(Engine::STATIC_MESH, "Test_Mesh", mesh_data);

     Engine::Mesh_Handle mesh_handle = Engine::mesh_handle("Test_Mesh");

     Engine::Camera camera;

     camera.perspective = Engine::perspective_projection(Engine::radians(45),
                                                         (float)window.width()/(float)window.height(),
                                                         1.0f,
                                                         100.0f);

     camera.view = Engine::view_transform(Engine::Vector3f(0, 0, 0),
                                          Engine::Vector3f(0, 0, 0),
                                          Engine::Vector3f(0, 0, 0));

     Engine::set_active_camera(camera);

     auto t_start = std::chrono::high_resolution_clock::now();

     Engine::enable_graphics_option(Engine::DEPTH_TEST_OPTION);
     Engine::set_depth_func(Engine::DEPTH_LESS_FUNC);

     Engine::set_clear_color(0.5f, 0.6f, 0.7f, 1.0f);
     int32_t color_location = test_shader.uniform_id("color");
     int32_t mvp_location = test_shader.uniform_id("mvp");

     Engine::set_clear_color(0.5f, 0.6f, 0.7f, 1.0f);

     #define ENTS 10000

     std::vector<Engine::Entity> entities;

     for ( size_t ii = 0; ii < ENTS; ii++ ) {
          Engine::Entity entity = Engine::create_entity();
          entities.push_back(entity);

          Engine::add_components(entity, {Engine::component_id<Engine::Transform>(),
                                          Engine::component_id<Engine::Mesh_Info>(),
                                          Engine::component_id<Engine::Material>()});

          Engine::Transform* transform = Engine::get_component<Engine::Transform>(entity);

          transform->position = Engine::Vector3f(Engine::random_float(-2, 2), Engine::random_float(-2, 2), Engine::random_float(4, 10));
          transform->scale = Engine::Vector3f(0.1f, 0.1f, 0.0f);
          transform->rotation = Engine::Vector3f(70, 0, 0);

          Engine::Mesh_Info* mesh_info = Engine::get_component<Engine::Mesh_Info>(entity);
          mesh_info->handle = mesh_handle;

          Engine::Material* material_info = Engine::get_component<Engine::Material>(entity);
          material_info->shader_id = test_shader.id();
     }

     Engine::Vector3f cam_pos(0, 0, 0);
     Engine::Vector3f cam_rot(0, 0, 0);

     Engine::Render_Texture_Info texture_info(WINDOW_WIDTH, WINDOW_HEIGHT, Engine::Texture_Format::RGB_FORMAT, Engine::Data_Type::UNSIGNED_BYTE);

     Engine::Render_Texture base(texture_info);

     Engine::Render_Context& render_context = *Engine::Render_Context::instance();

     Engine::Material outline_material = { pass1_shader.id() };
     Outline_Pass outline_pass(outline_material);

     outline_pass.configure();

     Engine::Timer frame_time;

     frame_time.start();

     while( window.is_closed() == false ) {
          frame_time.start();
          window.update();

          Engine::enable_graphics_option(Engine::DEPTH_TEST_OPTION);
          Engine::set_depth_func(Engine::DEPTH_LESS_FUNC);

          render_context.bind();
          render_context.set_color_texture(&base, Engine::Attachment_Type::COLOR_ATTACHMENT_0);

          Engine::set_view_port(0, 0, window.width(), window.height());

          Engine::graphics_clear(Engine::COLOR_BUFFER_CLEAR | Engine::DEPTH_BUFFER_CLEAR);

          //Engine::use_program(test_shader.id());

          //test_shader.set_uniform_float3(color_location, 0.3f, 0, 0.3f);

          if ( Engine::is_key_pressed(Engine::KEY_W) ) {
               cam_pos.z -= 0.1f;
          } else if ( Engine::is_key_pressed(Engine::KEY_S) ) {
               cam_pos.z += 0.1f;
          }

          if ( Engine::is_key_pressed(Engine::KEY_A) ) {
               cam_rot.y += 1;
          } else if ( Engine::is_key_pressed(Engine::KEY_D) ) {
               cam_rot.y -= 1;
          }
#if 0
          Engine::Matrix4f view_transform = Engine::view_transform(cam_pos,
                                                                   Engine::Vector3f(0, 0, 0),
                                                                   cam_rot);
#endif
          auto t_now = std::chrono::high_resolution_clock::now();
          float time = std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_start).count();
          Engine::update_systems(0.0f);
#if 0
          Engine::Entity_Group group({Engine::component_id<Engine::Mesh_Info>(),
                                      Engine::component_id<Engine::Transform>()});

          Engine::Component_Data_Array<Engine::Transform> trans_infos(group);
          Engine::Component_Data_Array<Engine::Mesh_Info> mesh_infos(group);

          for ( size_t ii = 0; ii < entities.size(); ii++ ) {
               Engine::Transform& trans = trans_infos[ii];
               Engine::Mesh_Info mesh_info = mesh_infos[ii];

               Engine::bind_mesh(mesh_info.handle);

               trans.rotation = Engine::Vector3f(time*30, time*20, time*40);
               Engine::Matrix4f model_transform = Engine::model_transform(trans.position,
                                                                          trans.scale,
                                                                          trans.rotation);

               Engine::Matrix4f mvp = camera.perspective * camera.view * model_transform;
               test_shader.set_uniform_mat4(mvp_location, (Engine::Matrix4f*)&mvp);

               Engine::draw_elements_data(Engine::TRIANGLE_MODE, 6, Engine::UNSIGNED_INT, 0);
          }
#endif
          outline_pass.execute(render_context);
          render_context.bit_to_screen();
          window.swap_buffers();
          float dt = (float)frame_time.elapsed_milli_sec();
          LOG("DT %fms", dt);
     }
}

