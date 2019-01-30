#ifndef __MATERIAL_MANAGER_H__
#define __MATERIAL_MANAGER_H__

#include <string>
#include "Engine.h"

namespace Engine {
namespace Material_Manager {

Rc_t init( void );
Material_Handle register_material( std::string material_name, Material material );
Material_Handle get_material_handle( std::string material_name );
Material* get_material( Material_Handle handle );
Material* get_material( std::string material_name );

} // end namespace Material_Manager
} // end namespace Engine

#endif //__MATERIAL_MANAGER_H__
