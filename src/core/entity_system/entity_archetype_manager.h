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
    std::vector<arche_comp_node_t*>*         comp_nodes_vec;
    std::unordered_map<uint64_t, uint64_t>*  comp_map;       //map comp id to vector pos
    std::unordered_map<uint64_t, uint64_t>*  idx_map;        //map location to entity
    std::unordered_map<uint64_t, uint64_t>*  entity_map;     //map entity to vector location
} archetype_node_t;

typedef struct {
    std::vector<archetype_node_t*>*             archetype_nodes;
    std::unordered_map<std::string, uint64_t>*  archetype_map;
    std::unordered_map<uint64_t, uint64_t>*     entity_map;
} entity_archetype_manager_t;

class CORE_API Entity_Archetype_Manager {
private:
    entity_archetype_manager_t*         entity_archetype_manager;
    static Entity_Archetype_Manager*    instance;

    void expand_comp_node( arche_comp_node_t* component_node );

    UhRC_t init( void );
public:
    static Entity_Archetype_Manager* get_instance();

    /**
        Register an archetype to a string name that will allow them to get this archetype back at a later date.

        @param archetype        holds the archetype data.
        @param archetype_name   name to map to the passed archetype.

        @return UhRC_t returns a return code.
    */
    UhRC_t register_archetype( Entity_Archetype archetype, std::string archetype_name );

    UhRC_t register_entity( Entity entity, std::string archetype_name );

    uint8_t* get_component_data( Entity entity, uint64_t component_id );

    template<typename T> T* get_component_data( Entity entity );

    //UhRC_t remove_entity( Entity entity );
};

template<typename T>
T* Entity_Archetype_Manager::get_component_data( Entity entity )
{
    return (T*)get_component_data(entity, Component_Manager::get_instance()->id<T>());
}

} // end namespace core

#endif // __ENTITY_ARCHETYPE_MANAGER_H__
