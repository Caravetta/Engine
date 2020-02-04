#include "basic_renderer.h"
#include "ecs.h"
#include "gtx/string_cast.hpp"

namespace Engine {

char light_pass_vert[] = "                                                                      \
               		 #version 330 core\n                                                   \
                                                                                     		 \
					 layout(location = 0) in vec3 vertexPosition_modelspace;\n             \
                                                                                     		 \
					 out vec2 uv;\n                                                        \
                                                                                     		 \
               		 void main(){\n                                                        \
					 	gl_Position = vec4(vertexPosition_modelspace, 1);\n               \
						uv = (vertexPosition_modelspace.xy+vec2(1,1))/2.0;\n              \
               		 }\n                                                                   \
              			";

char light_pass_frag[] = "                                                                                                             \
					 #version 330 core\n                                                                                          \
										                                                                                     \
					 out vec4 FragColor;\n                                                                                        \
										                                                                                     \
					 in vec2 uv;\n                                                                                                \
									                                                                                          \
					 uniform sampler2D gPosition;\n                                                                               \
				      uniform sampler2D gNormal;\n                                                                                 \
					 uniform sampler2D gAlbedoSpec;\n                                                                             \
												                                                                           \
					 struct Light {\n                                                                                             \
    				      	vec3 Position;\n                                                                                         \
    					 	vec3 Color;\n                                                                                            \
    					 	float Linear;\n                                                                                          \
    						float Quadratic;\n                                                                                       \
					 };\n                                                                                                         \
							                                                                                                    \
					 void main()\n                                                                                                \
					 {\n                                                                                                          \
						vec3 viewPos = vec3(0, 0, 0);\n                                                                          \
							                                                                                                    \
						Light light;\n                                                                                           \
						light.Position = vec3(0.5, 0.1, -7);\n                                                                   \
						light.Color = vec3(1, 1, 0);\n                                                                           \
						light.Linear = 0.7;\n                                                                                    \
						light.Quadratic = 1.8;\n                                                                                 \
												                                                                           \
    					 	// retrieve data from gbuffer\n                                                                          \
    					 	vec3 FragPos = texture(gPosition, uv).rgb;\n                                                             \
    					  	vec3 Normal = texture(gNormal, uv).rgb;\n                                                                \
    						vec3 Diffuse = texture(gAlbedoSpec, uv).rgb;\n                                                           \
																                                                       \
    						// then calculate lighting as usual\n                                                                    \
    						vec3 lighting  = Diffuse * 0.9; // hard-coded ambient component\n                                        \
    						vec3 viewDir  = normalize(viewPos - FragPos);\n                                                          \
																		                                             \
        					// diffuse\n                                                                                             \
        					vec3 lightDir = normalize(light.Position - FragPos);\n                                                   \
        					vec3 diffuse = max(dot(Normal, lightDir), 0.0) * Diffuse * light.Color;\n                                \
        					// attenuation\n                                                                                         \
        					float distance = length(light.Position - FragPos);\n                                                     \
        					float attenuation = 1.0 / (1.0 + light.Linear * distance + light.Quadratic * distance * distance);\n     \
        					diffuse *= attenuation;\n                                                                                \
        					lighting += diffuse;\n                                                                                   \
   	 					FragColor = vec4(lighting, 1.0);\n                                                                       \
					 }\n                                                                                                          \
					";

char pass_frag1[] = "                                                                                         \
               #version 330 core\n                                                                            \
                out vec4 color;\n                                                                             \
                in vec2 uv;\n                                                                                 \
                                                                                                              \
               uniform sampler2D text;\n                                                                      \
               mat3 sx = mat3( 1.0, 2.0, 1.0, 0.0, 0.0, 0.0, -1.0, -2.0, -1.0 );\n                            \
               mat3 sy = mat3( 1.0, 0.0, -1.0, 2.0, 0.0, -2.0, 1.0, 0.0, -1.0 );\n                            \
               void main()\n                                                                                  \
               {\n                                                                                            \
                 vec3 diffuse = texture(text, uv.st).rgb;\n                                                   \
                 mat3 I;\n                                                                                    \
                 for (int i=0; i<3; i++) {\n                                                                  \
                    for (int j=0; j<3; j++) {\n                                                               \
                         vec3 sample  = texelFetch(text, ivec2(gl_FragCoord) + ivec2(i-1,j-1), 0 ).rgb;\n     \
                         I[i][j] = length(sample);\n                                                          \
                    }\n                                                                                       \
                 }\n                                                                                          \
                 float gx = dot(sx[0], I[0]) + dot(sx[1], I[1]) + dot(sx[2], I[2]);\n                         \
                 float gy = dot(sy[0], I[0]) + dot(sy[1], I[1]) + dot(sy[2], I[2]);\n                         \
                 float g = sqrt(pow(gx, 2.0)+pow(gy, 2.0));\n                                                 \
                 color = vec4(diffuse - vec3(g), 1.0);\n                                                      \
               }\n                                                                                            \
              ";

Engine::Render_Texture* _outline;
struct Outline_Pass : public Engine::Render_Pass {
     Engine::Material* _material;

     Outline_Pass( Engine::Material& material )
     {
          _material = &material;
     };

     void configure( void )
     {
		Engine::Camera camera = get_active_camera();
          Engine::Render_Texture_Info texture_info(camera.window->width(), camera.window->height(),
										 Engine::Texture_Format::RGB_FORMAT, Engine::Data_Type::UNSIGNED_BYTE);
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

Outline_Pass* outline_pass;
int width = 0;
int height = 0;

void Basic_Renderer::init( void )
{
     // Setup G Buffer
     Engine::Render_Texture_Info format(800, 600, Engine::Texture_Format::RGB_16F_FORMAT,
                                        Engine::Texture_Format::RGB_FORMAT, Engine::Data_Type::FLOAT_DATA);

     position_texture = new Engine::Render_Texture(format);
     normal_texture = new Engine::Render_Texture(format);

     Engine::Render_Texture_Info albformat(800, 600, Engine::Texture_Format::RGB_FORMAT,
                                           Engine::Texture_Format::RGB_FORMAT, Engine::Data_Type::UNSIGNED_BYTE);

     albedo_texture = new Engine::Render_Texture(albformat);
     lighting_texture = new Engine::Render_Texture(albformat);

     Engine::Render_Texture_Info depthformat(800, 600, Engine::Texture_Format::DEPTH24_STENCIL8_FORMAT,
                                             Engine::Texture_Format::DEPTH_STENCIL, Engine::Data_Type::UNSIGNED_INT_24_8);
     depth_texture = new Engine::Render_Texture(depthformat);

	std::vector<Engine::Shader_String> shader_strings = {{Engine::VERTEX_SHADER, light_pass_vert, sizeof(light_pass_vert)},
											   {Engine::FRAGMENT_SHADER, pass_frag1, sizeof(pass_frag1)}};
	lighting_shader = new Engine::Shader(shader_strings);

     Engine::add_shader(lighting_shader->id(), *lighting_shader);
	outline_material.shader_id = lighting_shader->id();
	outline_pass = new Outline_Pass(outline_material);
	outline_pass->configure();
#if 1
	std::vector<Engine::Shader_String> shader_strings1 = {{Engine::VERTEX_SHADER, light_pass_vert, sizeof(light_pass_vert)},
											    {Engine::FRAGMENT_SHADER, light_pass_frag, sizeof(light_pass_frag)}};
	lighting_shader1 = new Engine::Shader(shader_strings1);
#endif
}

int l_width = 800;
int l_height = 600;

void Basic_Renderer::update( float time_step )
{
     Engine::Entity_Group group({Engine::component_id<Engine::Mesh_Info>(),
                                 Engine::component_id<Engine::Transform>(),
                                 Engine::component_id<Engine::Material>()});

     Engine::Component_Data_Array<Engine::Transform> trans_infos(group);
     Engine::Component_Data_Array<Engine::Mesh_Info> mesh_infos(group);
     Engine::Component_Data_Array<Engine::Material> material_infos(group);

     Engine::Camera camera = get_active_camera();

     // Check to see if we need to regen textures since window changed size //REMOVE
     if ( width != camera.window->width() ||
          height != camera.window->height() ) {

          width = camera.window->width();
          height = camera.window->height();

          position_texture->reload(width, height);
          normal_texture->reload(width, height);
          albedo_texture->reload(width, height);
          lighting_texture->reload(width, height);
          depth_texture->reload(width, height);
          _outline->reload(width, height);
          l_width = width;
          l_height = height;
     }

     Engine::Render_Context* render_context = Engine::Render_Context::instance();

     size_t num_entites = trans_infos.size();

     // Attach the G Buffer
     render_context->bind();

     render_context->set_color_texture(albedo_texture, Engine::Attachment_Type::COLOR_ATTACHMENT_0);
     render_context->set_color_texture(position_texture, Engine::Attachment_Type::COLOR_ATTACHMENT_1);
     render_context->set_color_texture(normal_texture, Engine::Attachment_Type::COLOR_ATTACHMENT_2);
     render_context->set_depth_texture(depth_texture);

     Engine::graphics_clear(Engine::COLOR_BUFFER_CLEAR | Engine::DEPTH_BUFFER_CLEAR);

     Engine::Attachment_Type attachments[3] = { Engine::Attachment_Type::COLOR_ATTACHMENT_0,
                                                Engine::Attachment_Type::COLOR_ATTACHMENT_1,
                                                Engine::Attachment_Type::COLOR_ATTACHMENT_2 };

     Engine::set_draw_buffers(attachments, 3);
     Engine::enable_graphics_option(Engine::DEPTH_TEST_OPTION);
     Engine::set_depth_func(Engine::DEPTH_LESS_FUNC);

     Engine::graphics_clear(Engine::COLOR_BUFFER_CLEAR | Engine::DEPTH_BUFFER_CLEAR);


     /** Start G Buffer Pass **/
     for ( size_t ii = 0; ii < num_entites; ii++ ) {
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

          int mvp_location = shader.uniform_id("per");
          if ( mvp_location != -1 ) {
               shader.set_uniform_mat4(mvp_location, (Engine::Matrix4f*)&camera.perspective);
          }

          mvp_location = shader.uniform_id("view");
          if ( mvp_location != -1 ) {
               shader.set_uniform_mat4(mvp_location, (Engine::Matrix4f*)&camera.view);
          }

          mvp_location = shader.uniform_id("model");
          if ( mvp_location != -1 ) {
               shader.set_uniform_mat4(mvp_location, (Engine::Matrix4f*)&model_transform);
          }

          Engine::draw_elements_data(Engine::TRIANGLE_MODE, indc, Engine::UNSIGNED_INT, 0);
     }


     Engine::disable_graphics_option(Engine::DEPTH_TEST_OPTION);

     render_context->clear_color_texture(Engine::Attachment_Type::COLOR_ATTACHMENT_1);
     render_context->clear_color_texture(Engine::Attachment_Type::COLOR_ATTACHMENT_2);
     /** End G Buffer Pass **/

     // render passes go here
	outline_pass->execute(*render_context);

     /** Start Lighting Pass **/
     Engine::Render_Texture* end_texure = render_context->get_color_texture(Engine::Attachment_Type::COLOR_ATTACHMENT_0);

     Engine::bind_texture(Texture_Unit::TEXTURE_UNIT_0, position_texture->texture());
     Engine::bind_texture(Texture_Unit::TEXTURE_UNIT_1, normal_texture->texture());
     Engine::bind_texture(Texture_Unit::TEXTURE_UNIT_2, end_texure->texture());

	render_context->set_color_texture(lighting_texture, Attachment_Type::COLOR_ATTACHMENT_0);
	use_program(lighting_shader1->id());

	int32_t texture_pos = lighting_shader1->uniform_id("gPosition");
	int32_t texture_norm = lighting_shader1->uniform_id("gNormal");
	int32_t texture_alb = lighting_shader1->uniform_id("gAlbedoSpec");

	lighting_shader1->set_uniform_int1(texture_pos, 0);
	lighting_shader1->set_uniform_int1(texture_norm, 1);
	lighting_shader1->set_uniform_int1(texture_alb, 2);

	uint32_t buff_id = render_context->quad_id();
	bind_vertex_array(buff_id);
	draw_data(Engine::TRIANGLE_MODE, 0, 6);
	bind_vertex_array(0);

     Engine::bind_texture(Texture_Unit::TEXTURE_UNIT_0, 0);
     Engine::bind_texture(Texture_Unit::TEXTURE_UNIT_1, 0);
     Engine::bind_texture(Texture_Unit::TEXTURE_UNIT_2, 0);
     /** End Lighting Pass **/

     //render_context->clear_color_texture(Engine::Attachment_Type::DEPTH_STENCIL_ATTACHMENT);
}

void Basic_Renderer::shutdown( void )
{

}

} // end namespace Engine

