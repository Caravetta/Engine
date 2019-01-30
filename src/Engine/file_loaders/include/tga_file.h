#ifndef __TGA_FILE_H__
#define __TGA_FILE_H__

#include <string>
#include "Engine_Types.h"

namespace Engine {

Rc_t load_tga_file( std::string file_path, Texture* texture );

} // end namespace Engine

#endif //__TGA_FILE_H__
