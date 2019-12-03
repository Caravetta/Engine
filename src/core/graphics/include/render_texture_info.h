#ifndef __RENDER_TEXTURE_INFO_H__
#define __RENDER_TEXTURE_INFO_H__

#include "core_common.h"
#include "platform_graphics.h"

namespace Engine {

struct Render_Texture_Info {
private:
     int __width;
     int __height;
     Texture_Format __format;
     Texture_Format __internal_format;
     Data_Type __type;

public:
     Render_Texture_Info( int width, int height, Texture_Format internal_format,
                          Texture_Format format, Data_Type type );
     Render_Texture_Info( int width, int height, Texture_Format format, Data_Type type );
     int width( void );
     int height( void );
     Texture_Format format( void );
     Texture_Format internal_format( void );
     Data_Type type( void );
};

} // end namespace Engine

#endif //__RENDER_TEXTURE_INFO_H__
