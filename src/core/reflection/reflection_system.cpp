#include <unordered_map>
#include "reflection_system.h"
#include "crc32.h"

namespace Engine {
namespace Reflection {

struct Reflection_System {
     std::unordered_map<uint32_t, Meta_Base*> meta_map;
};

Reflection_System* reflection_system = NULL;

Rc_t init_reflection_system( void )
{
     reflection_system = new (std::nothrow) Reflection_System;
     if ( reflection_system == NULL ) {
          return MEMORY_ALLOC_FAILED;
     }

     Meta_Base_Registrar::register_type(Registrar_Base_Types::META_STRUCT_TYPE);
     return SUCCESS;
}

bool register_type( const Meta_Base* type )
{
     uint32_t crc = crc32( type->__name);

     std::unordered_map<uint32_t, Meta_Base*>& meta_map = reflection_system->meta_map;
     if ( meta_map.find(crc) == meta_map.end() ) {

     } else {
          LOG_ERROR("%s already registered", type->__name);
          return false;
     }

     type->meta_register();

     return true;
}

} // end namespace Reflection
} // end namespace Engine

