#include "render_texture.h"

namespace Engine {

Render_Texture::Render_Texture( Render_Texture_Info& texture_info )
{
     //gen texture here
     __texture_handle = create_texture(texture_info.width(), texture_info.height(), NULL, Texture_Format::RGB_FORMAT);
}

Render_Texture::~Render_Texture( void )
{
     //TODO(JOSH): need to handle
}

void Render_Texture::reload( int32_t width, int32_t height )
{
     delete_texture(__texture_handle);
     __texture_handle = create_texture(width, height, NULL, Texture_Format::RGB_FORMAT);
}

Texture_Handle Render_Texture::texture( void )
{
     return __texture_handle;
}

} // end namespace Engine

