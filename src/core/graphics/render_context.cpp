#include <vector>
#include "render_context.h"

namespace Engine {

char blit_vert[] = "                                                                 \
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

char blit_frag[] = "                                        \
               #version 330 core\n                          \
                out vec3 color_out;\n                       \
                in vec2 uv;\n                               \
                                                            \
               uniform sampler2D text;\n                    \
               void main()\n                                \
               {\n                                          \
                   color_out = texture(text, uv).rgb;\n     \
               }\n                                          \
              ";


static const float g_quad_vertex_buffer_data[] = {
          -1.0f, -1.0f, 0.0f,
           1.0f, -1.0f, 0.0f,
          -1.0f,  1.0f, 0.0f,
          -1.0f,  1.0f, 0.0f,
           1.0f, -1.0f, 0.0f,
           1.0f,  1.0f, 0.0f,
};

Render_Context* Render_Context::__instance = NULL;

Render_Context* Render_Context::instance( void )
{
     if ( __instance == NULL ) {
          __instance = new (std::nothrow) Render_Context;
          if ( __instance != NULL ) {
               __instance->init();
          }
     }

     return __instance;
}

Render_Context::Render_Context( void )
{
     __fbo = INVALID_FBO_HANDLE;
     __depth_texture = NULL;
	__blit_shader = NULL;
}

Render_Context::~Render_Context( void )
{
     //TODO(JOSH): need to clean up FBO
}

void Render_Context::init( void )
{
     __fbo = create_fbo();

     __fbo_vertex_array_id = create_vertex_array();
     __fbo_vertexbuffer_id = create_vertex_buffer();
     bind_vertex_array(__fbo_vertex_array_id);
     bind_vertex_buffer(ARRAY_BUFFER, __fbo_vertexbuffer_id);
     buffer_vertex_data(ARRAY_BUFFER, (uint8_t*)g_quad_vertex_buffer_data, sizeof(g_quad_vertex_buffer_data), STATIC_DRAW);
     define_vertex_attrib(0, 3, false, Engine::FLOAT_DATA, 3 * sizeof(float), 0);
	enable_vertex_attrib(0);
     bind_vertex_buffer(ARRAY_BUFFER, 0);
     bind_vertex_array(0);

	if ( __blit_shader == NULL ) {
		std::vector<Shader_String> blit_shader_strings = {{VERTEX_SHADER, blit_vert, sizeof(blit_vert)},
												{FRAGMENT_SHADER, blit_frag, sizeof(blit_frag)}};
		__blit_shader = new (std::nothrow) Shader(blit_shader_strings);
	}
}

void Render_Context::set_color_texture( Render_Texture* texture, Attachment_Type attach_type )
{
     if ( attach_type > MAX_COLOR_TEXTURES ) {
          LOG_ERROR("%s: Exceeds max color textures", __FUNCTION__);
          return;
     }
     __color_textures[attach_type] = texture;
     set_fbo_color_texture(texture->texture(), attach_type);
}

Render_Texture* Render_Context::get_color_texture( Attachment_Type attach_type )
{
     Render_Texture* tmp = __color_textures[attach_type];
     return __color_textures[attach_type];
}

void Render_Context::clear_color_texture( Attachment_Type attach_type )
{
     if ( attach_type > MAX_COLOR_TEXTURES ) {
          LOG_ERROR("%s: Exceeds max color textures", __FUNCTION__);
          return;
     }

     set_fbo_color_texture(0, attach_type);
}

void Render_Context::set_depth_texture( Render_Texture* texture )
{
     __depth_texture = texture;
     set_fbo_color_texture(texture->texture(), Attachment_Type::DEPTH_STENCIL_ATTACHMENT);
}

Render_Texture* Render_Context::cur_depth_texture( void )
{
     return __depth_texture;
}

uint32_t Render_Context::quad_id( void )
{
     return __fbo_vertex_array_id;
}

void Render_Context::bind( void )
{
     if ( __fbo != INVALID_FBO_HANDLE ) {
          bind_fbo(__fbo);
     }
}

void Render_Context::unbind( void )
{
     unbind_fbo();
}

void Render_Context::bit_to_screen( void )
{
     unbind_fbo();
	graphics_clear(Engine::COLOR_BUFFER_CLEAR | Engine::DEPTH_BUFFER_CLEAR);
	use_program(__blit_shader->id());
     //TODO(JOSH): make this take in the color buffer
	bind_texture(Texture_Unit::TEXTURE_UNIT_0, __color_textures[0]->texture());
	int32_t texture_location = __blit_shader->uniform_id("text");
	__blit_shader->set_uniform_int1(texture_location, 0);
     bind_vertex_array(__fbo_vertex_array_id);
	draw_data(Engine::TRIANGLE_MODE, 0, 6);
     bind_vertex_array(0);
}

} // end namespace Engine

