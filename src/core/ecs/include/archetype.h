#ifndef __ARCHETYPE_H__
#define __ARCHETYPE_H__

#include <vector>
#include <string>
#include <unordered_map>
#include "return_codes.h"
#include "component.h"
#include "entity.h"
#include "core_common.h"

namespace Engine {

enum Archetype_Usage {
     ARCHETYPE_COMPONENT,
     ARCHETYPE_SHARED,
     ARCHETYPE_TAG,
};

struct Archetype_Comp_Info {
     Component_ID id;
     Archetype_Usage usage;
};

struct ENGINE_API Archetype {
     std::unordered_map<Component_ID, uint64_t>   component_id_map;
     std::vector<Archetype_Comp_Info>             component_info_vec;
     size_t                                       archetype_size;

     Archetype( void );
     template<typename T> Rc_t add_component( void );
     template<typename T> Rc_t add_shared_component( void );
     template<typename T> Rc_t add_tag( void );
};

Rc_t init_archetype_system( void );
Rc_t add_archetype( Archetype archetype, const std::string name );
Rc_t add_entity( const Entity entity, const std::string archetype_name );
Rc_t get_data( const Entity entity, const Component_ID id );
Rc_t add_component( const Entity entity, const Component_ID id );
Rc_t remove_component( const Entity entity, const Component_ID id );

template<typename T>
Rc_t Archetype::add_component( void )
{
     Rc_t rc = SUCCESS;
     Archetype_Comp_Info comp_info;
     comp_info.id = get_component_id<T>();
     comp_info.usage = ARCHETYPE_COMPONENT;

     if ( comp_info.id != INVALID_COMPONENT ) {
          // check to see if the component was already added
          UNORDERED_MAP_ITER(Component_ID, uint64_t) id_iter = component_id_map.find(comp_info.id);
          if ( id_iter == component_id_map.end() ) {
               component_info_vec.push_back(comp_info);
               component_id_map.insert({comp_info.id, component_info_vec.size() - 1});
          } else {
               rc = ENGINE_ERROR;
          }
     } else {
          rc = NOT_VALID_COMPONENT;
     }

     return rc;
}

template<typename T>
Rc_t Archetype::add_tag( void )
{
     Rc_t rc = SUCCESS;
     Archetype_Comp_Info comp_info;
     comp_info.id = get_component_id<T>();
     comp_info.usage = ARCHETYPE_TAG;

     if ( comp_info.id != INVALID_COMPONENT ) {
          // check to see if the component was already added
          UNORDERED_MAP_ITER(Component_ID, uint64_t) id_iter = component_id_map.find(comp_info.id);
          if ( id_iter == component_id_map.end() ) {
               component_info_vec.push_back(comp_info);
               component_id_map.insert({comp_info.id, component_info_vec.size() - 1});
          } else {
               rc = ENGINE_ERROR;
          }
     } else {
          rc = INVALID_COMPONENT;
     }

     return rc;
}

template<typename T>
Rc_t Archetype::add_shared_component( void )
{
     Rc_t rc = SUCCESS;
     Archetype_Comp_Info comp_info;
     comp_info.id = get_component_id<T>();
     comp_info.usage = ARCHETYPE_SHARED;

     if ( comp_info.id != INVALID_COMPONENT ) {
          // check to see if the component was already added
          UNORDERED_MAP_ITER(Component_ID, uint64_t) id_iter = component_id_map.find(comp_info.id);
          if ( id_iter == component_id_map.end() ) {
               component_info_vec.push_back(comp_info);
               component_id_map.insert({comp_info.id, component_info_vec.size() - 1});
          } else {
               rc = ENGINE_ERROR;
          }
     } else {
          rc = INVALID_COMPONENT;
     }

     return rc;
}

} // end namespace Engine

#endif // __ARCHETYPE_H__
