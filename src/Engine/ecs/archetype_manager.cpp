#include <utility>
#include "archetype_manager.h"
#include "system.h"
#include "system_manager.h"
#include "Engine_Types.h"
#include "entity_manager.h"

namespace Engine {
namespace Archetype_Manager {

#define COMP_RESIZE_SIZE 10

typedef struct {
    u64     total_elements;
    u64     empty_idx;
    u64*    empty_idx_p;
    u64     total_entities;
    u64*    total_entities_p;
    u32     component_id;
    Array*  data_array;
} arche_comp_node_t;

typedef struct {
    std::vector<arche_comp_node_t*>*    comp_nodes_vec;
    std::unordered_map<u64, u64>*       comp_map;       //map comp id to vector pos
    std::unordered_map<u64, u64>*       idx_map;        //map location to entity
    std::vector<Entity>                 entity_map;
} archetype_node_t;

typedef struct {
    std::vector<archetype_node_t*>*         archetype_nodes;
    std::unordered_map<std::string, u64>*   archetype_map;
} archetype_manager_t;

archetype_manager_t* archetype_manager;

Rc_t init( void )
{
    archetype_manager = new (std::nothrow) archetype_manager_t;
    if ( archetype_manager == NULL ) {
        LOG_ERROR("Failed to allocate memory for archetype_manager");
        return MEMORY_ALLOC_FAILED;
    }

    archetype_manager->archetype_map = new (std::nothrow) std::unordered_map<std::string, u64>;
    if ( archetype_manager->archetype_map == NULL ) {
        LOG_ERROR("Failed to allocate memory for archetype_manager->archetype_map");
        return MEMORY_ALLOC_FAILED;
    }

    archetype_manager->archetype_nodes = new (std::nothrow) std::vector<archetype_node_t*>;
    if ( archetype_manager->archetype_nodes == NULL ) {
        LOG_ERROR("Failed to allocate memory for archetype_manager->archetype_nodes");
        return MEMORY_ALLOC_FAILED;
    }

    return SUCCESS;
}

void update_entity_counts( void )
{
    archetype_node_t* current_arche_node = NULL;
    arche_comp_node_t* current_comp_node = NULL;

    for ( u32 ii = 0; ii < archetype_manager->archetype_nodes->size(); ++ii ) {
        current_arche_node = archetype_manager->archetype_nodes->at(ii);
        for ( u32 jj = 0; jj < current_arche_node->comp_nodes_vec->size(); ++jj ) {
            current_comp_node = current_arche_node->comp_nodes_vec->at(jj);
            current_comp_node->total_entities = current_comp_node->empty_idx;
        }
    }
}

Rc_t register_entity( const Entity entity, internal_entity_id* intern_entity_id, const std::string archetype_name )
{
    CHECK( archetype_manager != NULL );

    UNORDERED_MAP_ITERATOR(std::string, u64) arche_idx = archetype_manager->archetype_map->find(archetype_name);
    if ( arche_idx != archetype_manager->archetype_map->end() ) {
        archetype_node_t* tmp_archetype_node = archetype_manager->archetype_nodes->at(arche_idx->second);

        // map entity id to arche idx
        intern_entity_id->archetype = arche_idx->second;

        // map entity id to data idx in comp data
        intern_entity_id->index = tmp_archetype_node->comp_nodes_vec->at(0)->empty_idx;

        // map data idx to entity id
        tmp_archetype_node->idx_map->insert({ tmp_archetype_node->comp_nodes_vec->at(0)->empty_idx, entity.id });

        u64 entity_idx = tmp_archetype_node->comp_nodes_vec->at(0)->empty_idx;

        if ( entity_idx == tmp_archetype_node->comp_nodes_vec->at(0)->total_elements) {
            tmp_archetype_node->entity_map.resize(tmp_archetype_node->entity_map.size() + COMP_RESIZE_SIZE);
        }

        tmp_archetype_node->entity_map[intern_entity_id->index] = entity;

        u64 total_elements = 0;
        arche_comp_node_t* current_comp_node = NULL;
        size_t comp_size = 0;

        // loop through all the components in arche and init the data location / check if data needs to be resized
        for (u64 ii = 0; ii < tmp_archetype_node->comp_nodes_vec->size(); ++ii) {
            current_comp_node = tmp_archetype_node->comp_nodes_vec->at(ii);
            comp_size = get_component_size(current_comp_node->component_id);
            total_elements = current_comp_node->total_elements;

            // check to see if we need to resize data
            if ( current_comp_node->empty_idx == total_elements ) {
                current_comp_node->data_array->resize(comp_size * (total_elements + COMP_RESIZE_SIZE));
                current_comp_node->total_elements = total_elements + COMP_RESIZE_SIZE;
            }

            // call the allocator for this component ( because C++ sucks )
            component_create_function init_func = Component_Manager::get_component_create(current_comp_node->component_id);
            init_func(&(current_comp_node->data_array->at(entity_idx * comp_size)));
            current_comp_node->empty_idx += 1;
        }

        return SUCCESS;
    }

    CHECK_INFO( arche_idx == archetype_manager->archetype_map->end(),
                    "Archetype " << archetype_name << " is not registered" );

    return ARCHETYPE_DOES_NOT_EXIST;
}

u8* get_component_data_generic( const internal_entity_id intern_entity_id, const u32 component_id )
{
    CHECK( archetype_manager != NULL );

    archetype_node_t* tmp_archetype_node = archetype_manager->archetype_nodes->at(intern_entity_id.archetype);

    // Get the comp idx for the passed component ID.
    UNORDERED_MAP_ITERATOR(u64, u64) comp_iter = tmp_archetype_node->comp_map->find(component_id);
    if ( comp_iter != tmp_archetype_node->comp_map->end() ) {

        arche_comp_node_t* tmp_comp_node = tmp_archetype_node->comp_nodes_vec->at(comp_iter->second);

        size_t comp_size = get_component_size(component_id); //TODO(JOSH): add comp size to the comp_node

        return &(tmp_comp_node->data_array->at(intern_entity_id.index * comp_size));
    }
    CHECK_INFO( comp_iter == tmp_archetype_node->comp_map->end(),
                    "Component ID " << component_id << " not a part or this archetype" );

    return NULL;
}

Rc_t remove_entity( const internal_entity_id intern_entity_id )
{
    CHECK( archetype_manager != NULL );

    archetype_node_t* tmp_archetype_node = archetype_manager->archetype_nodes->at(intern_entity_id.archetype);
    u32 num_comps = (u32)tmp_archetype_node->comp_nodes_vec->size();

    if ( (tmp_archetype_node->comp_nodes_vec->at(0)->empty_idx - 1) == intern_entity_id.index ) {
        // this entity is at the end not need to swap data around

        arche_comp_node_t* current_comp_node = NULL;

        for ( u32 ii = 0; ii < num_comps; ++ii ) {
            current_comp_node = tmp_archetype_node->comp_nodes_vec->at(ii);
            current_comp_node->empty_idx = current_comp_node->empty_idx - 1;
        }

        return SUCCESS;
    } else {
        // Deleting this entity will create a hole in the data.
        // Need to move last element here to plug up hole.

        u64 end_idx = 0;
        Array* comp_data = NULL;
        size_t comp_size = 0;
        arche_comp_node_t* comp_node = NULL;

        // Loop through to swap all the comp data.
        for ( u32 ii = 0; ii < num_comps; ++ii ) {
            comp_node = tmp_archetype_node->comp_nodes_vec->at(ii);
            comp_size = get_component_size(comp_node->component_id);
            comp_data = comp_node->data_array;
            end_idx = comp_node->empty_idx - 1;
            component_copy_function copy_func = Component_Manager::get_component_copy(comp_node->component_id);

            copy_func(&(comp_data->at(end_idx * comp_size)), &(comp_data->at(intern_entity_id.index * comp_size)));
            comp_node->empty_idx = comp_node->empty_idx - 1;
        }

        // Update the entity lookup table.
        Entity* tmp_entity = &(tmp_archetype_node->entity_map[intern_entity_id.index]);

        *tmp_entity = tmp_archetype_node->entity_map[end_idx];
        internal_entity_id* internal_id_p = Entity_Manager::get_internal_id_pointer(*tmp_entity);
        internal_id_p->index = intern_entity_id.index;

        return SUCCESS;
    }

    return ENGINE_ERROR;
}

//TODO(JOSH): This need to be broken up into multiple function it is to large.
Rc_t register_archetype( Archetype archetype, std::string archetype_name )
{
    CHECK( archetype_manager != NULL );

    std::vector<archetype_node_t*>* archetype_nodes = archetype_manager->archetype_nodes;
    std::unordered_map<std::string, u64>* archetype_map = archetype_manager->archetype_map;
    UNORDERED_MAP_ITERATOR(std::string, u64) arche_idx = archetype_map->find(archetype_name);

    if ( arche_idx == archetype_map->end() ) {

        u64 arche_node_idx = archetype_nodes->size();

        archetype_map->insert({ archetype_name, arche_node_idx });

        // Allocate memory needed for new archetype node
        archetype_node_t* tmp_archetype_node =  new (std::nothrow) archetype_node_t;
        if ( tmp_archetype_node == NULL ) {
            LOG_ERROR("Failed to allocate memory for tmp_archetype_node");
            return MEMORY_ALLOC_FAILED;
        }

        archetype_nodes->push_back(tmp_archetype_node);

        u64 comp_node_idx = 0;
        size_t comp_size = 0;

        // Allocate memory needed for new archetype node elements
        tmp_archetype_node->comp_nodes_vec = new (std::nothrow) std::vector<arche_comp_node_t*>;
        if ( tmp_archetype_node->comp_nodes_vec == NULL ) {
            LOG_ERROR("Failed to allocate memory for tmp_archetype_node->comp_nodes_vec");
            return MEMORY_ALLOC_FAILED;
        }

        tmp_archetype_node->comp_map = new (std::nothrow) std::unordered_map<u64, u64>;
        if ( tmp_archetype_node->comp_map == NULL ) {
            LOG_ERROR("Failed to allocate memory for tmp_archetype_node->comp_map");
            return MEMORY_ALLOC_FAILED;
        }

        tmp_archetype_node->idx_map = new (std::nothrow) std::unordered_map<u64, u64>;
        if ( tmp_archetype_node->idx_map == NULL ) {
            LOG_ERROR("Failed to allocate memory for tmp_archetype_node->idx_map");
            return MEMORY_ALLOC_FAILED;
        }

        tmp_archetype_node->entity_map.resize(COMP_RESIZE_SIZE);

        // loop through all comps for arche and create new comp nodes for them
        for ( u64 ii = 0; ii < archetype.used_component_ids.size(); ii++ ) {
            comp_node_idx = tmp_archetype_node->comp_nodes_vec->size();

            DEBUG_LOG( archetype_name << " creating comp node for ID " << archetype.used_component_ids[ii] );

            // set mapping for comp ID to vec idx
            tmp_archetype_node->comp_map->insert({ archetype.used_component_ids[ii], comp_node_idx });

            arche_comp_node_t* tmp_comp_node = new (std::nothrow) arche_comp_node_t;
            if ( tmp_comp_node == NULL ) {
                LOG_ERROR("Failed to allocate memory for tmp_comp_node on iteration: " << ii);
                return MEMORY_ALLOC_FAILED;
            }

            tmp_archetype_node->comp_nodes_vec->push_back(tmp_comp_node);

            // setup the new component node
            tmp_comp_node->total_elements = COMP_RESIZE_SIZE;
            tmp_comp_node->empty_idx = 0;
            tmp_comp_node->empty_idx_p = &(tmp_comp_node->empty_idx);
            tmp_comp_node->total_entities = 0;
            tmp_comp_node->total_entities_p = &(tmp_comp_node->total_entities);
            tmp_comp_node->component_id = archetype.used_component_ids[ii];

            comp_size = get_component_size((u32)archetype.used_component_ids[ii]);

            tmp_comp_node->data_array = new Array;
            tmp_comp_node->data_array->resize(comp_size * COMP_RESIZE_SIZE);
        }

        bool should_add = false;
        UNORDERED_MAP_ITERATOR(u64, u64) current_comp;

        //get a pointer to vector containing all systems
        std::vector<System*>* systems = System_Manager::get_system_vec();

        // go through all systems to see if they care about this archetype
        for ( u64 jj = 0; jj < systems->size(); ++jj ) {
            should_add = true;

            // loop through all the system components
            for ( u64 ll = 0; ll < systems->at(jj)->component_list.size(); ++ll ) {
                current_comp = tmp_archetype_node->comp_map->find(systems->at(jj)->component_list[ll]);
                if ( current_comp == tmp_archetype_node->comp_map->end() ) {
                    should_add = false;
                    break;
                }
            }

            if ( should_add == true ) {
                DEBUG_LOG( "Adding " << archetype_name << " to " << systems->at(jj)->name );

                //TODO(JOSH): Currently we are sending all the comps to the system should only send ones they care about.

                // loop through all the comp and add them to this system
                for ( u64 kk = 0; kk < tmp_archetype_node->comp_nodes_vec->size(); ++kk ) {
                    systems->at(jj)->add_component_data(&tmp_archetype_node->comp_nodes_vec->at(kk)->total_entities_p,
                                                       tmp_archetype_node->comp_nodes_vec->at(kk)->component_id,
                                                       &tmp_archetype_node->comp_nodes_vec->at(kk)->data_array);
                }
            }
        }

        return SUCCESS;
    }

    CHECK_INFO( arche_idx != archetype_map->end(),
                "Archetype " << archetype_name << " is already mapped at idx " << arche_idx->second );

    return ARCHETYPE_EXISTS;
}

} //end namespace Archetype_Manager
} //end namespace core

