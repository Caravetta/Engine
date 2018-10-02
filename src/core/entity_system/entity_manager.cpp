#include "entity_manager.h"

namespace core {

Entity_Manager* Entity_Manager::instance = NULL;

#define ENTITY_RESIZE_SIZE 1000

void Entity_Manager::increase_entity_vec( void )
{
    size_t current_size = entity_manager.entity_ids.size();

    CHECK( (current_size + ENTITY_RESIZE_SIZE) < U32_MAX );

    entity_manager.entity_ids.resize( current_size + ENTITY_RESIZE_SIZE );

    // loop through new nodes and set them up
    for (; current_size < entity_manager.entity_ids.size(); current_size++ ) {
        entity_manager.entity_ids[current_size].active = 0;
        entity_manager.entity_ids[current_size].index = current_size;
    }
}

void Entity_Manager::reduce_entity_vec( void )
{
    //TODO(JOSH): need to implement.
    CHECK_INFO( 0, "_reduce_entity_vec not implemented" );
}

UhRC_t Entity_Manager::init( void )
{
    entity_manager.next_entity_idx = 0;

    increase_entity_vec();

    return SUCCESS;
}

Entity_Manager* Entity_Manager::get_instance()
{
    if ( instance == NULL ) {
        LOG("Initializing Entity_Manager");

        instance = new (std::nothrow) Entity_Manager;
        if ( instance == NULL ) {
            CHECK_INFO( 0, "Failed to allocate Entity_Archetype_Manager" );
            return NULL;
        }

        UhRC_t rc = instance->init();
        if ( rc != SUCCESS ) {
            delete instance;
            instance = NULL;
        }
    }

    return instance;
}

Entity Entity_Manager::create_entity( std::string archetype_name )
{
    Entity return_entity = {0};

    Entity_Archetype_Manager* archetype_manager = Entity_Archetype_Manager::get_instance();
    if ( archetype_manager == NULL ) {
        CHECK_INFO( 0, "Failed to get Entity_Archetype_Manager");
        return return_entity;
    }

    // check to see if there is a node in the free vector
    if ( !entity_manager.free_entity_idx.empty() ) {
        uint32_t free_idx = entity_manager.free_entity_idx.back();
        entity_manager.free_entity_idx.pop_back();

        entity_manager.entity_ids[free_idx].active = HANDLE_SET_ACTIVE;
        return_entity = entity_manager.entity_ids[free_idx];
    } else {
        // check to see if we have run out of entities in the vector
        if ( entity_manager.entity_ids.size() == entity_manager.next_entity_idx ) {
            increase_entity_vec();
        }
        entity_manager.entity_ids[entity_manager.next_entity_idx].active = HANDLE_SET_ACTIVE;
        return_entity.id = entity_manager.entity_ids[entity_manager.next_entity_idx].id;
        entity_manager.next_entity_idx++;
    }

    archetype_manager->register_entity(return_entity, archetype_name);

    return return_entity;
}

UhRC_t Entity_Manager::delete_entity( Entity entity )
{
    Entity_Archetype_Manager* archetype_manager = Entity_Archetype_Manager::get_instance();
    if ( archetype_manager == NULL ) {
        CHECK_INFO( 0, "Failed to get Entity_Archetype_Manager");
        return ENGINE_ERROR;
    }

    // check to see if the Entity is valid
    if ( entity.id == entity_manager.entity_ids[entity.index].id ) {
        entity_manager.entity_ids[entity.index].phase++;
        entity_manager.entity_ids[entity.index].active = HANDLE_SET_NON_ACTIVE;

        entity_manager.free_entity_idx.push_back(entity.index);

        //TODO(JOSH); Call the archetype manager and tell it to drop this entity
        CHECK_INFO( 0, "We are not telling the archetype manager to drop this entity");

        return SUCCESS;
    }

    return ERROR_INVALID_ENTITY;
}

bool Entity_Manager::is_valid_entity( Entity entity )
{
    return (entity.id == entity_manager.entity_ids[entity.index].id);
}

} //end namespace core
