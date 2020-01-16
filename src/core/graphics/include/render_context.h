#ifndef __RENDER_CONTEXT_H__
#define __RENDER_CONTEXT_H__

#include "core_common.h"
#include "platform_graphics.h"
#include "render_texture.h"
#include "shader.h"

namespace Engine {

#define MAX_COLOR_TEXTURES 20

class Render_Context {
public:
     void set_color_texture( Render_Texture* texture, Attachment_Type attach_type );
     Render_Texture* get_color_texture( Attachment_Type attach_type );
     void clear_color_texture( Attachment_Type attach_type );
     void set_depth_texture( Render_Texture* texture );
     Render_Texture* cur_depth_texture( void );
     uint32_t quad_id( void );
     void bind( void );
     void unbind( void );
     void bit_to_screen( void );

     static Render_Context* instance( void );

private:
     Render_Context( void );
     ~Render_Context( void );
     void init( void );

     static Render_Context* __instance;
     Fbo_Handle __fbo;
     uint32_t __fbo_vertex_array_id;
     uint32_t __fbo_vertexbuffer_id;
     Render_Texture* __color_textures[MAX_COLOR_TEXTURES];
     Render_Texture* __depth_texture;
     Shader* __blit_shader;
};

} // end namespace Engine

#endif //__RENDER_CONTEXT_H__
