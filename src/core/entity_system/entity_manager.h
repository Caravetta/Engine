#ifndef __ENTITY_MANAGER_H__
#define __ENTITY_MANAGER_H__

#include <vector>
#include <utility>
#include <type_traits>
#include "../core_common.h"
#include "entity.h"
#include "../handle_system/handle.h"
#include "../component_system/component_manager.h"
#include "../component_system/component.h"
#include "../system/system_manager.h"
#include "entity_archetype_manager.h"

namespace core {

typedef struct {
    uint32_t                next_entity_idx;
    std::vector<Entity>     entity_ids;       // Vector of all Entity ids
    std::vector<uint32_t>   free_entity_idx;
} entity_manager_t;

class CORE_API Entity_Manager {
private:
    entity_manager_t entity_manager;
    static Entity_Manager* instance;

    UhRC_t init( void );
public:
    static Entity_Manager* get_instance();
    Entity create_entity( std::string archetype_name );
    UhRC_t delete_entity( Entity entity );
    bool is_valid_entity( Entity entity );

    //UhRC_t register_archetype( Entity_Archetype archetype, std::string archetype_name );

    template<typename T> UhRC_t add_component( Entity entity );
    template<typename T> UhRC_t remove_component( Entity entity );
    template<typename T> T* get_component( Entity entity );
    template<typename T> bool is_component_set( Entity entity );

private:
    void increase_entity_vec( void );
    void reduce_entity_vec( void );

};

template<typename T>
UhRC_t Entity_Manager::add_component( Entity entity )
{
    //TODO(JOSH): need to implement.
    CHECK_INFO( 0, "entity_manager_add_component not implemented" );
    return SUCCESS;
}

template<typename T>
UhRC_t Entity_Manager::remove_component( Entity entity )
{
    //TODO(JOSH): need to implement.
    CHECK_INFO( 0, "entity_manager_remove_component not implemented" );
    return SUCCESS;
}

template<typename T>
T* Entity_Manager::get_component( Entity entity )
{
    return Entity_Archetype_Manager::get_instance()->get_component_data<T>(entity);
}

} // end namespace core

#endif //__ENTITY_MANAGER_H__
