#include "render_pass.h"

namespace Engine {

Render_Pass::Render_Pass( void )
{
     // Do nothing
}

void Render_Pass::blit( Render_Context& context, Render_Texture& source,
                        Render_Texture& dest, Material& material )
{
     context.set_color_texture(&dest, Attachment_Type::COLOR_ATTACHMENT_0);
     bind_texture(Texture_Unit::TEXTURE_UNIT_0, source.texture());
     Shader shader = get_shader(material.shader_id);

     use_program(shader.id());
     int32_t texture_location = shader.uniform_id("text");
     shader.set_uniform_int1(texture_location, 0);


     uint32_t buff_id = context.quad_id();
     //enable_vertex_attrib(0);
     bind_vertex_array(buff_id);
     draw_data(Engine::TRIANGLE_MODE, 0, 6);
     bind_vertex_array(0);
}

} // end namespace Engine

