#ifndef __ECS__H__
#define __ECS__H__

#include <vector>
#include <string>
#include "entity.h"
#include "component.h"
#include "archetype.h"
#include "return_codes.h"
#include "core_common.h"

namespace Engine {

Rc_t init_ecs( void );

ENGINE_API Entity create_entity( const std::string archetype_name );
ENGINE_API std::vector<Entity> batch_create_entity( const std::string archetype_name, const uint32_t count );
ENGINE_API Rc_t delete_entity( const Entity entity );
ENGINE_API Rc_t batch_delete_entity( const std::vector<Entity> entities );

ENGINE_API Rc_t register_archetype( Archetype archetype, const std::string name );

template<typename T> Rc_t register_component( void );
template<typename T> Rc_t register_tag( void );
template<typename T> Rc_t register_system( void );

template<typename T> Rc_t add_component( const Entity entity );
template<typename T> Rc_t remove_component( const Entity entity );

template<typename T> T* get_component_data( const Entity entity );

Rc_t init_systems( void );
Rc_t update_systems( void );
Rc_t shutdown_systems( void );

template<typename T>
Rc_t register_component( void )
{
     Component_Info temp_comp;

     temp_comp.type = COMPONENT_TYPE;
     temp_comp.create_function = component_create<T>;
     temp_comp.copy_function = component_copy<T>;
     temp_comp.size = sizeof(T);

     register_component_info(get_component_id<T>(), temp_comp);

     return SUCCESS;
}

template<typename T>
Rc_t register_tag( void )
{
     return SUCCESS;
}

template<typename T>
Rc_t register_system( void )
{
     return SUCCESS;
}

template<typename T>
Rc_t add_component( const Entity entity )
{
     return SUCCESS;
}

template<typename T>
Rc_t remove_component( const Entity entity )
{

}

} // end namespace Engine

#endif // __ECS__H__

