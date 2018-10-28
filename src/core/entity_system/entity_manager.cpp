#include "entity_manager.h"

namespace core {
namespace Entity_Manager {

#define ENTITY_RESIZE_SIZE 1000

typedef struct {
    uint32_t                        next_entity_idx;
    std::vector<Entity>             entity_ids;       // Vector of all Entity ids
    std::vector<internal_entity_id> internal_entity_ids;
    std::vector<uint32_t>           free_entity_idx;
} entity_manager_t;

entity_manager_t entity_manager;

void _increase_entity_vec( void )
{
    size_t current_size = entity_manager.entity_ids.size();

    CHECK( (current_size + ENTITY_RESIZE_SIZE) < U32_MAX );

    entity_manager.entity_ids.resize( current_size + ENTITY_RESIZE_SIZE );
    entity_manager.internal_entity_ids.resize( current_size + ENTITY_RESIZE_SIZE );

    // loop through new nodes and set them up
    for (; current_size < entity_manager.entity_ids.size(); current_size++ ) {
        entity_manager.entity_ids[current_size].active = 0;
        entity_manager.entity_ids[current_size].index = current_size;
    }
}

void _reduce_entity_vec( void )
{
    //TODO(JOSH): need to implement.
    CHECK_INFO( 0, "_reduce_entity_vec not implemented" );
}

UhRC_t Entity_Manager::init( void )
{
    entity_manager.next_entity_idx = 0;

    _increase_entity_vec();

    return SUCCESS;
}

Entity create_entity( std::string archetype_name )
{
    Entity return_entity = {0};
    uint64_t internal_idx;

    // check to see if there is a node in the free vector
    if ( !entity_manager.free_entity_idx.empty() ) {
        uint32_t free_idx = entity_manager.free_entity_idx.back();
        entity_manager.free_entity_idx.pop_back();

        entity_manager.entity_ids[free_idx].active = HANDLE_SET_ACTIVE;
        internal_idx = free_idx;
        return_entity = entity_manager.entity_ids[free_idx];
    } else {
        // check to see if we have run out of entities in the vector
        if ( entity_manager.entity_ids.size() == entity_manager.next_entity_idx ) {
            _increase_entity_vec();
        }
        internal_idx = entity_manager.next_entity_idx;
        entity_manager.entity_ids[entity_manager.next_entity_idx].active = HANDLE_SET_ACTIVE;
        return_entity.id = entity_manager.entity_ids[entity_manager.next_entity_idx].id;
        entity_manager.next_entity_idx++;
    }

    //TODO(JOSH): pass in internal entity id
    Entity_Archetype_Manager::register_entity(return_entity, &entity_manager.internal_entity_ids[internal_idx], archetype_name);

    return return_entity;
}

UhRC_t delete_entity( Entity entity )
{
    // check to see if the Entity is valid
    if ( entity.id == entity_manager.entity_ids[entity.index].id ) {
        entity_manager.entity_ids[entity.index].phase++;
        entity_manager.entity_ids[entity.index].active = HANDLE_SET_NON_ACTIVE;

        entity_manager.free_entity_idx.push_back(entity.index);

        //TODO(JOSH): Call the archetype manager and tell it to drop this entity
        CHECK_INFO( 0, "We are not telling the archetype manager to drop this entity");

        return SUCCESS;
    }

    return ERROR_INVALID_ENTITY;
}

bool is_valid_entity( Entity entity )
{
    return (entity.id == entity_manager.entity_ids[entity.index].id);
}

internal_entity_id get_internal_id( Entity entity )
{
    return entity_manager.internal_entity_ids[entity.index];
}

} // end namespace Entity_Manager
} // end namespace core

