#include "entity_manager.h"
#include "archetype_manager.h"

namespace Engine {
namespace Entity_Manager {

#define ENTITY_RESIZE_SIZE 1000

typedef struct {
    std::string archetype_name;
    u32         add_count;
} entity_add_node_t;

typedef struct {
    u32                             next_entity_idx;
    std::vector<Entity>             entity_ids; // Vector of all Entity ids
    std::vector<internal_entity_id> internal_entity_ids;
    std::vector<u32>                free_entity_idx;
    std::vector<Entity>             entities_to_free;
} entity_manager_t;

entity_manager_t entity_manager;

void _increase_entity_vec( void )
{
    size_t current_size = entity_manager.entity_ids.size();

    CHECK( (current_size + ENTITY_RESIZE_SIZE) < U32_MAX );

    entity_manager.entity_ids.resize( current_size + ENTITY_RESIZE_SIZE );
    entity_manager.internal_entity_ids.resize( current_size + ENTITY_RESIZE_SIZE );

    // loop through new nodes and set them up
    for (; current_size < entity_manager.entity_ids.size(); ++current_size ) {
        entity_manager.entity_ids[current_size].active = 0;
        entity_manager.entity_ids[current_size].index = current_size;
    }
}

void _reduce_entity_vec( void )
{
    //TODO(JOSH): need to implement.
    CHECK_INFO( 0, "_reduce_entity_vec not implemented" );
}

Rc_t init( void )
{
    entity_manager.next_entity_idx = 0;

    _increase_entity_vec();

    return SUCCESS;
}

void update( void )
{
    // check to see if entities need to be cleaned up
    if ( !entity_manager.entities_to_free.empty() ) {
        u32 current_idx = 0;

        for ( u32 ii = 0; ii < entity_manager.entities_to_free.size(); ++ii ) {
            current_idx = entity_manager.entities_to_free[ii].index;

            Archetype_Manager::remove_entity(entity_manager.internal_entity_ids[current_idx]);
            entity_manager.entity_ids[current_idx].phase++;
            entity_manager.entity_ids[current_idx].active = HANDLE_SET_NON_ACTIVE;
            entity_manager.free_entity_idx.push_back(current_idx);
        }

        entity_manager.entities_to_free.clear();
    }

    Archetype_Manager::update_entity_counts();
}

bool is_valid_entity( const Entity entity )
{
    if ( entity.index < entity_manager.entity_ids.size() ) {
        return (entity.id == entity_manager.entity_ids[entity.index].id);
    }

    CHECK_INFO(0, "Entity ID: " << entity.id << " is not a valid enitiy");

    return false;
}

internal_entity_id get_internal_id( const Entity entity )
{
    if ( entity.index < entity_manager.internal_entity_ids.size() ) {
        return entity_manager.internal_entity_ids[entity.index];
    }

    internal_entity_id tmp_id;
    tmp_id.id = 0;

    CHECK_INFO(0, "Entity ID: " << entity.id << " is not a valid enitiy");

    return tmp_id;
}

internal_entity_id* get_internal_id_pointer( const Entity entity )
{
    if ( entity.index < entity_manager.internal_entity_ids.size() ) {
        return &entity_manager.internal_entity_ids[entity.index];
    }

    CHECK_INFO(0, "Entity ID: " << entity.id << " is not a valid enitiy");

    return NULL;
}

Entity create_entity( const std::string archetype_name )
{
    Entity return_entity = {0};
    u64 internal_idx;

    //TODO(JOSH): need to check to see if passed archetype_name is valid

    // check to see if there is a node in the free vector
    if ( !entity_manager.free_entity_idx.empty() ) { //TODO(JOSH): should be able to get ride of this branch
        u32 free_idx = entity_manager.free_entity_idx.back();
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

    Archetype_Manager::register_entity(return_entity, &entity_manager.internal_entity_ids[internal_idx], archetype_name);

    return return_entity;
}

Rc_t delete_entity( const Entity entity )
{
    Rc_t rc = ERROR_INVALID_ENTITY;

    // check to see if the Entity is valid
    if ( entity.index < entity_manager.entity_ids.size() ) {
        if ( entity.id == entity_manager.entity_ids[entity.index].id ) {
            // we defer the free of an entity until the end of the frame
            entity_manager.entities_to_free.push_back(entity);

            rc = SUCCESS;
        }
    }

    return rc;
}

} // end namespace Entity_Manager
} // end namespace Engine

