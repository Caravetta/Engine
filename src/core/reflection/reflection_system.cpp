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
     Meta_Info_Base_Registrar::register_meta_info();
     return SUCCESS;
}

bool register_type( Meta_Base* type )
{
     uint32_t crc = crc32( type->__name);

     std::unordered_map<uint32_t, Meta_Base*>& meta_map = reflection_system->meta_map;
     if ( meta_map.find(crc) == meta_map.end() ) {
          meta_map.insert(std::make_pair(crc, type));
     } else {
          LOG_ERROR("%s already registered", type->__name);
          return false;
     }

     type->meta_register();

     return true;
}

Meta_Struct* get_meta_struct( const char* name )
{
     uint32_t crc = crc32(name);

     std::unordered_map<uint32_t, Meta_Base*>::const_iterator iter = reflection_system->meta_map.find(crc);
     if ( iter == reflection_system->meta_map.end() ) {
          LOG_ERROR("Could Not Find Struct %s", name);
          return NULL;
     }

     return (Meta_Struct*)iter->second;
}

Meta_Info* get_meta_info( const char* name )
{
     uint32_t id = crc32(name);
     std::unordered_map<uint32_t, const Meta_Info*>& map = Meta_Info_Base_Registrar::meta_map;

     std::unordered_map<uint32_t, const Meta_Info*>::const_iterator iter = map.find(id);
     if ( iter != map.end() ) {
          return (Meta_Info*)iter->second;
     }

     return NULL;
}

} // end namespace Reflection
} // end namespace Engine

