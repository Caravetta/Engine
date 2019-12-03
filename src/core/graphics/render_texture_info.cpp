#include "render_texture_info.h"

namespace Engine {

Render_Texture_Info::Render_Texture_Info( int width, int height, Texture_Format internal_format,
                                          Texture_Format format, Data_Type type )
{
     __width = width;
     __height = height;
     __format = format;
     __internal_format = internal_format;
     __type = type;
}

Render_Texture_Info::Render_Texture_Info( int width, int height, Texture_Format format, Data_Type type )
{
     __width = width;
     __height = height;
     __format = format;
     __internal_format = format;
     __type = type;
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

Data_Type Render_Texture_Info::type( void )
{
     return __type;
}

Texture_Format Render_Texture_Info::internal_format( void )
{
     return __internal_format;
}

} // end namespace Engine

