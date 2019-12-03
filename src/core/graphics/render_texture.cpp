#include "render_texture.h"

namespace Engine {

Render_Texture::Render_Texture( Render_Texture_Info& texture_info )
{
     //gen texture here
     __internal_format = texture_info.internal_format();
     __format = texture_info.format();
     __type = texture_info.type();
     __texture_handle = create_texture(texture_info.width(), texture_info.height(),
                                       NULL, __internal_format, __format, __type);
}

Render_Texture::~Render_Texture( void )
{
     //TODO(JOSH): need to handle
}

void Render_Texture::reload( int32_t width, int32_t height )
{
     delete_texture(__texture_handle);
     __texture_handle = create_texture(width, height, NULL, __internal_format, __format, __type);
}

Texture_Handle Render_Texture::texture( void )
{
     return __texture_handle;
}

} // end namespace Engine

