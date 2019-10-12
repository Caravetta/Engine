#include "render_texture.h"

namespace Engine {

Render_Texture::Render_Texture( Render_Texture_Info& texture_info )
{
     //gen texture here
     __texture_handle = create_texture(texture_info.width(), texture_info.height());
}

Render_Texture::~Render_Texture( void )
{
     //TODO(JOSH): need to handle
}

Texture_Handle Render_Texture::texture( void )
{
     return __texture_handle;
}

} // end namespace Engine

