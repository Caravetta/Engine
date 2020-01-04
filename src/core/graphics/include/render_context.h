#ifndef __RENDER_CONTEXT_H__
#define __RENDER_CONTEXT_H__

#include "core_common.h"
#include "platform_graphics.h"
#include "render_texture.h"
#include "shader.h"

namespace Engine {

class Render_Context {
private:
     Fbo_Handle __fbo;
     uint32_t __fbo_vertex_array_id;
     uint32_t __fbo_vertexbuffer_id;
     Render_Texture* __color_texture;
     Render_Texture* __depth_texture;
     Shader* __blit_shader;

public:
     Render_Context( void );
     ~Render_Context( void );
     void init( void );
     void set_color_texture( Render_Texture& texture, Attachment_Type attach_type );
     Render_Texture& cur_color_texture( void );
     void set_depth_texture( Render_Texture& texture );
     Render_Texture& cur_depth_texture( void );
     uint32_t quad_id( void );
     void bind( void );
     void unbind( void );
     void bit_to_screen( void );
};

} // end namespace Engine

#endif //__RENDER_CONTEXT_H__
