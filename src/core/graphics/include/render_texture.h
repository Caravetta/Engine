#ifndef __RENDER_TEXTURE_H__
#define __RENDER_TEXTURE_H__

#include "core_common.h"
#include "render_texture_info.h"
#include "platform_graphics.h"

namespace Engine {

struct Render_Texture {
private:
     Texture_Handle __texture_handle;

public:
     Render_Texture( Render_Texture_Info& texture_info );
     ~Render_Texture( void );
     Texture_Handle texture( void );
};

} // end namespace Engine

#endif //__RENDER_TEXTURE_H__
