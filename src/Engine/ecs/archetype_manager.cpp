#include <utility>
#include "archetype_manager.h"
#include "system.h"
#include "system_manager.h"
#include "Engine.h"
#include "entity_manager.h"

namespace Engine {
namespace Archetype_Manager {

#define COMP_RESIZE_SIZE 10

typedef struct {
    u64                 total_elements;
    u64                 empty_idx;
    u64*                empty_idx_p;
    u64                 total_entities;
    u64*                total_entities_p;
    u32                 component_id;
    Array*              data_array;
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
    ALLOC_RETURN_FAILURE( archetype_manager, archetype_manager_t );
    ALLOC_RETURN_FAILURE( archetype_manager->archetype_map, std::unordered_map<std::string, u64> );
    ALLOC_RETURN_FAILURE( archetype_manager->archetype_nodes, std::vector<archetype_node_t*> );

    return SUCCESS;
}

void update_entity_counts()
{
    //TODO(JOSH): need to clean this up
    for ( u32 ii = 0; ii < archetype_manager->archetype_nodes->size(); ++ii ) {
        for ( u32 jj = 0; jj < archetype_manager->archetype_nodes->at(ii)->comp_nodes_vec->size(); ++jj ) {
            archetype_manager->archetype_nodes->at(ii)->comp_nodes_vec->at(jj)->total_entities = archetype_manager->archetype_nodes->at(ii)->comp_nodes_vec->at(jj)->empty_idx;
        }
    }
}

Rc_t register_entity( Entity entity, internal_entity_id* intern_entity_id, std::string archetype_name )
{
    CHECK( archetype_manager != NULL );

    std::unordered_map<std::string, u64>::const_iterator arche_idx = archetype_manager->archetype_map->find(archetype_name);
    if ( arche_idx != archetype_manager->archetype_map->end() ) {
        u64 entity_idx = 0;
        archetype_node_t* tmp_archetype_node = archetype_manager->archetype_nodes->at(arche_idx->second);

        // map entity id to arche idx
        intern_entity_id->archetype = arche_idx->second;

        // map entity id to data idx in comp data
        intern_entity_id->index = tmp_archetype_node->comp_nodes_vec->at(0)->empty_idx;

        // map data idx to entity id
        tmp_archetype_node->idx_map->insert({ tmp_archetype_node->comp_nodes_vec->at(0)->empty_idx, entity.id });

        entity_idx = tmp_archetype_node->comp_nodes_vec->at(0)->empty_idx;

        if ( entity_idx == tmp_archetype_node->comp_nodes_vec->at(0)->total_elements) {
            tmp_archetype_node->entity_map.resize(tmp_archetype_node->entity_map.size() + COMP_RESIZE_SIZE);
        }

        tmp_archetype_node->entity_map[intern_entity_id->index] = entity;

        // loop through all the components in arche and init the data location / check if data needs to be resized
        for (u64 i = 0; i < tmp_archetype_node->comp_nodes_vec->size(); i++) {
            size_t comp_size = get_component_size(tmp_archetype_node->comp_nodes_vec->at(i)->component_id);

            // check to see if we need to resize data
            if ( tmp_archetype_node->comp_nodes_vec->at(i)->empty_idx == tmp_archetype_node->comp_nodes_vec->at(i)->total_elements ) {
                tmp_archetype_node->comp_nodes_vec->at(i)->data_array->resize(comp_size * (tmp_archetype_node->comp_nodes_vec->at(i)->total_elements + COMP_RESIZE_SIZE));
                tmp_archetype_node->comp_nodes_vec->at(i)->total_elements = tmp_archetype_node->comp_nodes_vec->at(i)->total_elements + COMP_RESIZE_SIZE;
            }

            // call the allocator for this component ( because C++ sucks )
            component_create_function init_func = Component_Manager::get_component_create(tmp_archetype_node->comp_nodes_vec->at(i)->component_id);
            init_func(&(tmp_archetype_node->comp_nodes_vec->at(i)->data_array->at(entity_idx * comp_size)));
            tmp_archetype_node->comp_nodes_vec->at(i)->empty_idx += 1;
        }

        return SUCCESS;
    }

    CHECK_INFO( arche_idx == archetype_manager->archetype_map->end(), "Archetype " << archetype_name << " is not registered" );

    return ARCHETYPE_DOES_NOT_EXIST;
}

u8* get_component_data_generic( internal_entity_id intern_entity_id, u32 component_id )
{
    CHECK( archetype_manager != NULL );

    archetype_node_t* tmp_archetype_node = archetype_manager->archetype_nodes->at(intern_entity_id.archetype);

    // Get the comp idx for the passed component ID.
    std::unordered_map<u64, u64>::const_iterator comp_idx = tmp_archetype_node->comp_map->find(component_id);
    if ( comp_idx != tmp_archetype_node->comp_map->end() ) {

        arche_comp_node_t* tmp_comp_node = tmp_archetype_node->comp_nodes_vec->at(comp_idx->second);

        size_t comp_size = get_component_size(component_id); //TODO(JOSH): add comp size to the comp_node

        return &(tmp_comp_node->data_array->at(intern_entity_id.index * comp_size));
    }
    CHECK_INFO( comp_idx == tmp_archetype_node->comp_map->end(),
                    "Component ID " << component_id << " not a part or this archetype" );

    return NULL;
}

Rc_t remove_entity( internal_entity_id intern_entity_id )
{
    //LOG("Want to remove index: " << intern_entity_id.index);

    archetype_node_t* tmp_archetype_node = archetype_manager->archetype_nodes->at(intern_entity_id.archetype);
    u32 num_comps = (u32)tmp_archetype_node->comp_nodes_vec->size();

    if ( (tmp_archetype_node->comp_nodes_vec->at(0)->empty_idx - 1) == intern_entity_id.index) {
        // this entity is at the end not need to swap data around

        for ( u32 ii = 0; ii < num_comps; ++ii ) {
            tmp_archetype_node->comp_nodes_vec->at(ii)->empty_idx = tmp_archetype_node->comp_nodes_vec->at(ii)->empty_idx - 1;
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

            //LOG("Moving comp_id " << comp_node->component_id << " from: " << end_idx << " to " << intern_entity_id.index);

            copy_func(&(comp_data->at(end_idx * comp_size)), &(comp_data->at(intern_entity_id.index * comp_size)));
            comp_node->empty_idx = comp_node->empty_idx - 1;
        }

        // Update the entity lookup table.
        tmp_archetype_node->entity_map[intern_entity_id.index] = tmp_archetype_node->entity_map[end_idx];
        internal_entity_id* internal_id_p = Entity_Manager::get_internal_id_pointer(tmp_archetype_node->entity_map[intern_entity_id.index]);
        internal_id_p->index = intern_entity_id.index;

        return SUCCESS;
    }

    return ENGINE_ERROR;
}

} //end namespace Archetype_Manager

Rc_t register_archetype( Archetype archetype, std::string archetype_name )
{
    CHECK( archetype_manager != NULL );

    std::vector<Archetype_Manager::archetype_node_t*>* archetype_nodes = Archetype_Manager::archetype_manager->archetype_nodes;
    std::unordered_map<std::string, u64>* archetype_map = Archetype_Manager::archetype_manager->archetype_map;
    std::unordered_map<std::string, u64>::const_iterator arche_idx = archetype_map->find(archetype_name);

    if ( arche_idx == archetype_map->end() ) {

        u64 arche_node_idx = archetype_nodes->size();

        archetype_map->insert({ archetype_name, arche_node_idx });

        Archetype_Manager::archetype_node_t* tmp_archetype_node = NULL;
        // Allocate memory needed for new archetype node
        ALLOC_RETURN_FAILURE( tmp_archetype_node, Archetype_Manager::archetype_node_t );

        archetype_nodes->push_back(tmp_archetype_node);

        u64 comp_node_idx = 0;
        size_t comp_size = 0;

        // Allocate memory needed for new archetype node elements
        ALLOC_RETURN_FAILURE( tmp_archetype_node->comp_nodes_vec, std::vector<Archetype_Manager::arche_comp_node_t*> );
        ALLOC_RETURN_FAILURE( tmp_archetype_node->comp_map, std::unordered_map<u64, u64> );
        ALLOC_RETURN_FAILURE( tmp_archetype_node->idx_map, std::unordered_map<u64, u64> );

        tmp_archetype_node->entity_map.resize(COMP_RESIZE_SIZE);

        // loop through all comps for arche and create new comp nodes for them
        for ( u64 i = 0; i < archetype.used_component_ids.size(); i++ ) {
            comp_node_idx = tmp_archetype_node->comp_nodes_vec->size();

            DEBUG_LOG( archetype_name << " creating comp node for ID " << archetype.used_component_ids[i] );

            // set mapping for comp ID to vec idx
            tmp_archetype_node->comp_map->insert({ archetype.used_component_ids[i], comp_node_idx });

            Archetype_Manager::arche_comp_node_t* tmp_comp_node = NULL;
            ALLOC_RETURN_FAILURE( tmp_comp_node, Archetype_Manager::arche_comp_node_t );

            tmp_archetype_node->comp_nodes_vec->push_back(tmp_comp_node);

            // setup the new component node
            tmp_comp_node->total_elements = COMP_RESIZE_SIZE;
            tmp_comp_node->empty_idx = 0;
            tmp_comp_node->empty_idx_p = &(tmp_comp_node->empty_idx);
            tmp_comp_node->total_entities = 0;
            tmp_comp_node->total_entities_p = &(tmp_comp_node->total_entities);
            tmp_comp_node->component_id = archetype.used_component_ids[i];

            comp_size = get_component_size((u32)archetype.used_component_ids[i]);

            tmp_comp_node->data_array = new Array;
            tmp_comp_node->data_array->resize(comp_size * COMP_RESIZE_SIZE);
        }

        bool should_add = false;
        std::unordered_map<u64, u64>::const_iterator current_comp;

        //get a pointer to vector containing all systems
        std::vector<System*>* systems = System_Manager::get_system_vec();

        // go through all systems to see if they care about this archetype
        for ( u64 j = 0; j < systems->size(); j++ ) {
            should_add = true;

            // loop through all the system components
            for ( u64 l = 0; l < systems->at(j)->component_list.size(); l++ ) {
                current_comp = tmp_archetype_node->comp_map->find(systems->at(j)->component_list[l]);
                if ( current_comp == tmp_archetype_node->comp_map->end() ) {
                    should_add = false;
                    break;
                }
            }

            if ( should_add == true ) {
                DEBUG_LOG( "Adding " << archetype_name << " to " << systems->at(j)->name );

                //TODO(JOSH): Currently we are sending all the comps to the system should only send ones they care about.

                // loop through all the comp and add them to this system
                for ( u64 k = 0; k < tmp_archetype_node->comp_nodes_vec->size(); k++ ) {
                    systems->at(j)->add_component_data(&tmp_archetype_node->comp_nodes_vec->at(k)->total_entities_p,
                                                       tmp_archetype_node->comp_nodes_vec->at(k)->component_id,
                                                       &tmp_archetype_node->comp_nodes_vec->at(k)->data_array);
                }
            }
        }

        return SUCCESS;
    }

    CHECK_INFO( arche_idx != archetype_map->end(), "Archetype " << archetype_name << " is already mapped at idx " << arche_idx->second );

    return ARCHETYPE_EXISTS;
}

} //end namespace core

