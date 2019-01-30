#ifndef __TEXTURE_MANAGER_H__
#define __TEXTURE_MANAGER_H__

#include "Engine.h"

namespace Engine {
namespace Texture_Manager {

Rc_t init( void );
uint32_t get_texture_id( Texture_Handle handle );
Texture_Handle load_to_graphics_api( Texture* texture );

} // end namespace Texture_Manager
} // end namespace Engine

#endif //__TEXTURE_MANAGER_H__
