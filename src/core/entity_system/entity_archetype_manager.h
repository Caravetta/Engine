#ifndef __ENTITY_ARCHETYPE_MANAGER_H__
#define __ENTITY_ARCHETYPE_MANAGER_H__

#include "../core_common.h"
#include "entity_archetype.h"
#include "entity.h"

namespace core {

typedef struct {
    uint64_t    total_elements;
    uint64_t    empty_idx;
    uint64_t*   empty_idx_p;
    uint64_t    component_id;
    uint8_t*    data;
    uint8_t**   data_p;
} arche_comp_node_t;

typedef struct {
    uint64_t total_components;
    std::vector<arche_comp_node_t>          comp_nodes_vec;
    std::unordered_map<uint64_t, uint64_t>  comp_map;       //map comp id to vector pos
    std::unordered_map<uint64_t, uint64_t>  idx_map;        //map location to entity
    std::unordered_map<uint64_t, uint64_t>  entity_map;     //map entity to vector location
} archetype_node_t;

typedef struct {
    std::vector<archetype_node_t*>*             archetype_nodes;
    std::unordered_map<std::string, uint64_t>*  archetype_map;
    std::unordered_map<uint64_t, uint64_t>*     entity_map;
} entity_archetype_manager_t;

CORE_API UhRC_t init_entity_archetype_manager( entity_archetype_manager_t* entity_archetype_manager );
CORE_API UhRC_t register_archetype( entity_archetype_manager_t* entity_archetype_manager, Entity_Archetype archetype, std::string archetype_name );
CORE_API UhRC_t register_entity( entity_archetype_manager_t* entity_archetype_manager, Entity entity, std::string archetype_name );
CORE_API uint8_t* get_component_data( entity_archetype_manager_t* entity_archetype_manager, Entity entity, uint64_t component_id );
CORE_API UhRC_t remove_entity( entity_archetype_manager_t* entity_archetype_manager, Entity entity );

template<typename T>
T* get_component_data( entity_archetype_manager_t* entity_archetype_manager, Entity entity )
{
    return NULL;
}

class CORE_API Entity_Archetype_Manager {
private:
    static Entity_Archetype_Manager*            instance;
    std::vector<archetype_node_t>               archetype_nodes;
    std::unordered_map<std::string, uint64_t>   archetype_map;    //map arche name to idx
    std::unordered_map<uint64_t, uint64_t>      entity_map;       //map entity to archetype_node_t

    void expand_comp_node( arche_comp_node_t* component_node );
public:
    static Entity_Archetype_Manager* get_instance();

    /**
        Register an archetype to a string name that will allow them to get this archetype back at a later date.

        @param archetype        holds the archetype data.
        @param archetype_name   name to map to the passed archetype.

        @return UhRC_t returns a return code.
    */
    UhRC_t register_archetype( Entity_Archetype archetype, std::string archetype_name );

    /**
        Cleans up any archetype that is marked as empty.

        @return none.
    */
    void cleanup_archetypes();

    UhRC_t add_entity( Entity entity, std::string archetype_name );

    uint8_t* get_component_data( Entity entity, uint64_t component_id );

    template<typename T> T* get_component_data( Entity entity );

    UhRC_t remove_entity( Entity entity );
};

template<typename T>
T* Entity_Archetype_Manager::get_component_data( Entity entity )
{
    return (T*)get_component_data(entity, Component_Manager::get_instance()->id<T>());
}

} // end namespace core

#endif // __ENTITY_ARCHETYPE_MANAGER_H__
