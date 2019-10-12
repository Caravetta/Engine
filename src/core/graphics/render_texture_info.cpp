#include "render_texture_info.h"

namespace Engine {

Render_Texture_Info::Render_Texture_Info( int width, int height, Texture_Format format )
{
     __width = width;
     __height = height;
     __format = format;
}

int Render_Texture_Info::width( void )
{
     return __width;
}

int Render_Texture_Info::height( void )
{
     return __height;
}

Texture_Format Render_Texture_Info::format( void )
{
     return __format;
}

} // end namespace Engine

