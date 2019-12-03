#ifndef __RENDER_TEXTURE_H__
#define __RENDER_TEXTURE_H__

#include "core_common.h"
#include "render_texture_info.h"
#include "platform_graphics.h"

namespace Engine {

struct Render_Texture {
private:
     Texture_Format __internal_format;
     Texture_Format __format;
     Data_Type      __type;
     Texture_Handle __texture_handle;

public:
     Render_Texture( Render_Texture_Info& texture_info );
     ~Render_Texture( void );
     void reload( int32_t width, int32_t height );
     Texture_Handle texture( void );
};

} // end namespace Engine

#endif //__RENDER_TEXTURE_H__
