#include "component_manager.h"
#include "archetype_manager.h"
#include "entity_manager.h"

namespace Engine {
namespace Component_Manager {

std::vector<component_info>* component_info_vec = NULL;

Rc_t init( void )
{
    component_info_vec = new (std::nothrow) std::vector<component_info>;
    if ( component_info_vec == NULL ) {
        LOG_ERROR("Failed to allocate memory for component_info_vec");
        return MEMORY_ALLOC_FAILED;
    }

    component_info_vec->resize( BASE_COMPONENT_COUNT );

    return SUCCESS;
}

component_create_function get_component_create( const u32 component_id )
{
    CHECK( component_info_vec != NULL );

    if ( component_id < component_info_vec->size() ) {
        return component_info_vec->at(component_id).create_function;
    }

    CHECK_INFO(0, "Comp ID: " << component_id << " not a valid component");

    return NULL;
}

component_copy_function get_component_copy( const u32 component_id )
{
    CHECK( component_info_vec != NULL );
    if ( component_id < component_info_vec->size() ) {
        return component_info_vec->at(component_id).copy_function;
    }

    CHECK_INFO(0, "Comp ID: " << component_id << " not a valid component");

    return NULL;
}

u32 get_max_components( void )
{
    CHECK( component_info_vec != NULL );
    return (u32)component_info_vec->size();
}

u64 get_component_size( const u32 component_id )
{
    CHECK( component_info_vec != NULL );

    if ( component_id < component_info_vec->size() ) {
        return component_info_vec->at(component_id).size;
    }

    CHECK_INFO(0, "Comp ID: " << component_id << " not a valid component");

    return 0;
}

void register_component_info( const u32 component_id, const component_info comp_info )
{
    CHECK( component_info_vec != NULL );

    if ( component_id < BASE_COMPONENT_COUNT ) {
        component_info_vec->at(component_id) = comp_info;
    } else {
        component_info_vec->push_back(comp_info);
    }
}

u8* get_component_data( const Entity entity, const u32 component_id )
{
    CHECK( component_info_vec != NULL );

    if ( component_id < component_info_vec->size() ) {
        return Archetype_Manager::get_component_data_generic(Entity_Manager::get_internal_id(entity), component_id);
    }

    CHECK_INFO(0, "Comp ID: " << component_id << " not a valid component");

    return NULL;
}

} // end namespace Component_Manager
} // end namespace Engine
