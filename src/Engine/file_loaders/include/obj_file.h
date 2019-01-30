#ifndef __OBJ_FILE_H__
#define __OBJ_FILE_H__

#include <string>
#include "Engine_Types.h"

namespace Engine {

Rc_t load_obj_file( std::string file_path, Mesh* mesh );

} // end namespace Engine

#endif //__OBJ_FILE_H__
