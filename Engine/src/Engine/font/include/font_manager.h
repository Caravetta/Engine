#ifndef __FONT_MANAGER_H__
#define __FONT_MANAGER_H__

#include <string>
#include "Engine_Types.h"

namespace Engine {
namespace Font_Manager {

void init();
Font_Handle load_font_file( std::string file_path );
uint32_t get_texture_id( Font_Handle handle, uint16_t font_size );

} // end namespace Font_Manager
} // end namespace Engine

#endif //__FONT_MANAGER_H__
