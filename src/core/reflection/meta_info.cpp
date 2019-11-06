#include <new>
#include "meta_info.h"
#include "crc32.h"
#include <type_traits>
#include <iostream>

namespace Engine {

Meta_Info::Meta_Info( void )
{
     // do nothing
}

#if 0
Meta_Info::~Meta_Info( void )
{
     // do nothing
}
#endif

Meta_Info* Meta_Info::create( void )
{
     return new (std::nothrow) Meta_Info();
}

void Meta_Info::populate_info( void )
{
     __populate_func(*this);
}

Meta_Info_Base_Registrar* Meta_Info_Base_Registrar::__s_head = NULL;
Meta_Info_Base_Registrar* Meta_Info_Base_Registrar::__s_tail = NULL;
std::unordered_map<uint32_t, const Meta_Info*> Meta_Info_Base_Registrar::meta_map;

Meta_Info_Base_Registrar::Meta_Info_Base_Registrar( void )
{
     __next = NULL;
}

Meta_Info_Base_Registrar::~Meta_Info_Base_Registrar( void )
{
     // do nothing
}

void Meta_Info_Base_Registrar::add_to_list( Meta_Info_Base_Registrar* registrar )
{
     if ( __s_tail != NULL ) {
          __s_tail->__next = registrar;
          __s_tail = registrar;
     } else {
          __s_tail = registrar;
          __s_head = registrar;
     }
}

void Meta_Info_Base_Registrar::add_meta_info( const Meta_Info* meta_info )
{
     uint32_t id = crc32(meta_info->__name);
     LOG("name: %s id: %" PRIu32 "", meta_info->__name, id);
     meta_map.insert({id, meta_info});
}

void Meta_Info_Base_Registrar::register_meta_info( void )
{
     for ( Meta_Info_Base_Registrar* cur_reg = __s_head; cur_reg; cur_reg = cur_reg->__next ) {
          cur_reg->meta_info_register();
     }

     std::unordered_map<uint32_t, const Meta_Info*>& map = Meta_Info_Base_Registrar::meta_map;
     std::unordered_map<uint32_t, const Meta_Info*>::const_iterator iter = map.begin();
     while ( iter != map.end() ) {

          Meta_Info* tmp = const_cast<Meta_Info*>(iter->second);
          tmp->populate_info();
          iter++;
     }
}

} // end namespace Engine

