#include "ecs.h"

namespace Engine {

Rc_t init_ecs( void )
{
    Rc_t rc = SUCCESS;

    rc = init_component_system();
    if ( rc != SUCCESS ) {
        LOG_ERROR("Failed to initialize component system");
        return rc;
    }

    rc = init_entity_system();
    if ( rc != SUCCESS ) {
        LOG_ERROR("Failed to initialize entity system");
        return rc;
    }

    return rc;
}

Entity create_entity( const std::string archetype_name )
{
    Entity entity = get_entity_id();
    return entity;
}

std::vector<Entity> batch_create_entity( const std::string archetype_name, const uint32_t count )
{
    std::vector<Entity> entity_list;

    entity_list.resize(count);

    for ( uint32_t ii = 0; ii < count; ++ii ) {
        entity_list[ii] = get_entity_id();
    }

    return entity_list;
}

Rc_t delete_entity( const Entity entity )
{
    return free_entity_id(entity);
}

Rc_t batch_delete_entity( const std::vector<Entity> entities )
{
    Rc_t rc = SUCCESS;
    for ( uint64_t ii = 0; ii < entities.size(); ++ii ) {
        rc = free_entity_id(entities[ii]);
        if ( rc != SUCCESS ) {
            LOG_ERROR("Index %" PRIu64 " is not a valid entity", ii);
        }
    }
    return rc;
}

Rc_t register_archetype( const Archetype archetype )
{
    return SUCCESS;
}

Rc_t init_systems( void )
{
    return SUCCESS;
}

Rc_t update_systems( void )
{
    return SUCCESS;
}

Rc_t shutdown_systems( void )
{
    return SUCCESS;
}

} // end namespace Engine

