#include <vector>
#include "entity.h"

namespace Engine {

#define ENTITY_BLOCK_SIZE 100

struct Entity_Manager {
    Handle_Manager handle_manager;
};

Entity_Manager* entity_manager = NULL;

Rc_t init_entity_system( void )
{
    Rc_t rc = SUCCESS;

    if ( entity_manager == NULL ) {
        entity_manager = new (std::nothrow) Entity_Manager;
        if ( entity_manager == NULL ) {
            rc = MEMORY_ALLOC_FAILED;
            LOG_ERROR("Failed to allocate memory for entity system");
        } else {
            entity_manager->handle_manager.set_block_size( ENTITY_BLOCK_SIZE );
        }
    } else {
        rc = ENGINE_ERROR;
        LOG_ERROR("Entity system all ready initialized");
    }

    return rc;
}

Entity get_entity_id( void )
{
    Entity entity;

    entity.handle = entity_manager->handle_manager.get_handle();

    return entity;
}

Rc_t free_entity_id( const Entity entity )
{
    Rc_t rc = INVALID_ENTITY;

    if ( entity_manager->handle_manager.valid_handle(entity.handle) ) {
        entity_manager->handle_manager.free_handle(entity.handle);
        rc = SUCCESS;
    }

    return rc;
}

} // end namespace Engine

