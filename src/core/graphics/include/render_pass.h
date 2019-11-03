#ifndef __RENDER_PASS_H__
#define __RENDER_PASS_H__

#include <string>
#include "core_common.h"
#include "render_texture.h"
#include "render_context.h"
#include "material.h"

namespace Engine {

struct Render_Pass {
     std::string pass_name;

     Render_Pass( void );

     virtual void configure( void ) {};
     virtual void execute( Render_Context& context ) {};
     virtual void cleanup( void ) {};

     void blit( Render_Context& context, Render_Texture& source,
                Render_Texture& dest, Material& material );
};

} // end namespace Engine

#endif //__RENDER_PASS_H__
