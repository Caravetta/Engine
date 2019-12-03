#include "basic_renderer.h"
#include "ecs.h"
#include "graphics.h"

namespace Engine {

char g_buf_vert[] = "                                            \
                      #version 330 core\n                        \
                      layout(location = 0) in vec3 Position;\n   \
                                                                 \
                      out vec3 FragPos;\n                        \
                                                                 \
                      uniform mat4 model;\n                      \
                      uniform mat4 view;\n                       \
                      uniform mat4 projection\n                  \
                                                                           \
                      void main()\n                                        \
                      {\n                                                  \
                         vec4 worldPos = model * vec4(Position, 1.0);\n    \
                         FragPos = worldPos.xyz;\n                         \
                         gl_Position = projection * view * worldPos;\n     \
                      }\n                                                  \
                    ";

char g_buf_frag[] = "                                                      \
                      #version 330 core\n                                  \
                      layout (location = 0) out vec3 gPosition;\n          \
                                                                           \
                      in vec3 FragPos;\n                                   \
                                                                           \
                      void main()\n                                        \
                      {\n                                                  \
                         gPosition = FragPos;\n                            \
                      }\n                                                  \
                    ";


Render_Texture* position_texture = NULL;

void Basic_Renderer::init( void )
{
     Render_Texture_Info position_format(800, 600, Engine::Texture_Format::RGB_16F_FORMAT,
                                         Engine::Texture_Format::RGB_FORMAT, Engine::Data_Type::FLOAT_DATA);
     position_texture = new (std::nothrow) Render_Texture(position_format);
}

void Basic_Renderer::update( float time_step )
{
     Engine::Entity_Group group({Engine::component_id<Engine::Mesh_Info>(),
                                 Engine::component_id<Engine::Transform>(),
                                 Engine::component_id<Engine::Material>()});

     Engine::Component_Data_Array<Engine::Transform> trans_infos(group);
     Engine::Component_Data_Array<Engine::Mesh_Info> mesh_infos(group);
     Engine::Component_Data_Array<Engine::Material> material_infos(group);

     Engine::Camera camera = get_active_camera();

     for ( size_t ii = 0; ii < trans_infos.size(); ii++ ) {
          Engine::Transform trans = trans_infos[ii];
          Engine::Mesh_Info mesh_info = mesh_infos[ii];
          Engine::Material material = material_infos[ii];

          Shader shader = get_shader(material.shader_id);

          use_program(shader.id());

          size_t indc = 0;
          Engine::bind_mesh(mesh_info.handle, indc);

          Engine::Matrix4f model_transform = Engine::model_transform(trans.position,
                                                                     trans.scale,
                                                                     trans.rotation);

          Engine::Matrix4f mvp = camera.perspective * camera.view * model_transform;

          int32_t mvp_location = shader.uniform_id("mvp");
          shader.set_uniform_mat4(mvp_location, (Engine::Matrix4f*)&mvp);

          Engine::draw_elements_data(Engine::TRIANGLE_MODE, indc, Engine::UNSIGNED_INT, 0);
     }
}

void Basic_Renderer::shutdown( void )
{

}

} // end namespace Engine

