#include "entity_archetype_manager.h"

namespace core {

Entity_Archetype_Manager* Entity_Archetype_Manager::instance = NULL;

Entity_Archetype_Manager* Entity_Archetype_Manager::get_instance()
{
    if ( instance == NULL ) {
        LOG("Initializing Entity_Archetype_Manager");

        instance = new (std::nothrow) Entity_Archetype_Manager;
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

UhRC_t Entity_Archetype_Manager::init( void )
{
    ALLOC_RETURN_FAILURE( entity_archetype_manager, entity_archetype_manager_t );
    ALLOC_RETURN_FAILURE( entity_archetype_manager->entity_map, std::unordered_map<uint64_t, uint64_t> );
    ALLOC_RETURN_FAILURE( entity_archetype_manager->archetype_map, std::unordered_map<std::string, uint64_t> );
    ALLOC_RETURN_FAILURE( entity_archetype_manager->archetype_nodes, std::vector<archetype_node_t*> );

    return SUCCESS;
}

UhRC_t Entity_Archetype_Manager::register_archetype( Entity_Archetype archetype, std::string archetype_name )
{
    CHECK( entity_archetype_manager != NULL );

    std::vector<archetype_node_t*>* archetype_nodes = entity_archetype_manager->archetype_nodes;
    std::unordered_map<std::string, uint64_t>* archetype_map = entity_archetype_manager->archetype_map;
    std::unordered_map<std::string, uint64_t>::const_iterator arche_idx = archetype_map->find(archetype_name);

    if ( arche_idx == archetype_map->end() ) {

        uint64_t arche_node_idx = archetype_nodes->size();

        archetype_map->insert({ archetype_name, arche_node_idx });

        archetype_node_t* tmp_archetype_node = NULL;
        // Allocate memory needed for new archetype node
        ALLOC_RETURN_FAILURE( tmp_archetype_node, archetype_node_t );

        archetype_nodes->push_back(tmp_archetype_node);

        uint64_t comp_node_idx = 0;
        size_t comp_size = 0;

        // Allocate memory needed for new archetype node elements
        ALLOC_RETURN_FAILURE( tmp_archetype_node->comp_nodes_vec, std::vector<arche_comp_node_t*> );
        ALLOC_RETURN_FAILURE( tmp_archetype_node->comp_map, std::unordered_map<uint64_t, uint64_t> );
        ALLOC_RETURN_FAILURE( tmp_archetype_node->idx_map, std::unordered_map<uint64_t, uint64_t> );
        ALLOC_RETURN_FAILURE( tmp_archetype_node->entity_map, std::unordered_map<uint64_t, uint64_t> );

        // loop through all comps for arche and create new comp nodes for them
        for (int i = 0; i < archetype.used_component_ids.size(); i++) {
            comp_node_idx = tmp_archetype_node->comp_nodes_vec->size();

            DEBUG_LOG( archetype_name << " " << archetype.used_component_ids[i] );

            // set mapping for comp ID to vec idx
            tmp_archetype_node->comp_map->insert({ archetype.used_component_ids[i], comp_node_idx });

            arche_comp_node_t* tmp_comp_node = NULL;
            ALLOC_RETURN_FAILURE( tmp_comp_node, arche_comp_node_t );

            tmp_archetype_node->comp_nodes_vec->push_back(tmp_comp_node);

            // setup the new component node
            tmp_comp_node->total_elements = 10;
            tmp_comp_node->empty_idx = 0;
            tmp_comp_node->empty_idx_p = &(tmp_comp_node->empty_idx);
            tmp_comp_node->component_id = archetype.used_component_ids[i];

            Component_Manager* component_manager  = Component_Manager::get_instance();
            if ( component_manager == NULL ) {
                CHECK_INFO( 0, "Failed to get Component_Manager" );
                return ENGINE_ERROR;
            }

            comp_size = component_manager->get_component_size(archetype.used_component_ids[i]);

            tmp_comp_node->data = (uint8_t*)malloc(comp_size * 10);
            tmp_comp_node->data_p = &(tmp_comp_node->data);
        }

        bool should_add = false;
        std::unordered_map<uint64_t, uint64_t>::const_iterator current_comp;
        System_Manager* system_manager = System_Manager::get_instance();

        if ( system_manager == NULL ) {
            CHECK_INFO( 0, "Failed to get System_Manager" );
            return ENGINE_ERROR;
        }

        // go through all systems to see if they care about this archetype
        for (int j = 0; j < system_manager->systems.size(); j++) {
            should_add = true;

            // loop through all the system components
            for (int l = 0; l < system_manager->systems[j]->component_list.size(); l++) {
                current_comp = tmp_archetype_node->comp_map->find(system_manager->systems[j]->component_list[l]);
                if ( current_comp == tmp_archetype_node->comp_map->end() ) {
                    should_add = false;
                    break;
                }
            }

            if ( should_add == true ) {
                DEBUG_LOG( "ADDING " << archetype_name << " to " << system_manager->systems[j]->name );

                // loop through all the comp and add them to this system
                for (int k = 0; k < tmp_archetype_node->comp_nodes_vec->size(); k++) {
                    system_manager->systems[j]->add_component_data(&tmp_archetype_node->comp_nodes_vec->at(k)->data_p,
                                                                   &tmp_archetype_node->comp_nodes_vec->at(k)->empty_idx_p,
                                                                   tmp_archetype_node->comp_nodes_vec->at(k)->component_id);
                }
            }
        }

        return SUCCESS;
    }

    CHECK_INFO( arche_idx =! archetype_map->end(), "Archetype " << archetype_name << " is already mapped at idx " << arche_idx->second );

    return ARCHETYPE_EXISTS;
}

UhRC_t Entity_Archetype_Manager::register_entity( Entity entity, std::string archetype_name )
{
    CHECK( entity_archetype_manager != NULL );

    std::unordered_map<std::string, uint64_t>::const_iterator arche_idx = entity_archetype_manager->archetype_map->find(archetype_name);
    if ( arche_idx != entity_archetype_manager->archetype_map->end() ) {
        uint64_t entity_idx = 0;
        archetype_node_t* tmp_archetype_node = entity_archetype_manager->archetype_nodes->at(arche_idx->second);

        // map entity id to arche idx
        entity_archetype_manager->entity_map->insert({ entity.id, arche_idx->second });

        // map entity id to data idx in comp data
        tmp_archetype_node->entity_map->insert({ entity.id, tmp_archetype_node->comp_nodes_vec->at(0)->empty_idx });

        // map data idx to entity id
        tmp_archetype_node->idx_map->insert({ tmp_archetype_node->comp_nodes_vec->at(0)->empty_idx, entity.id });

        entity_idx = tmp_archetype_node->comp_nodes_vec->at(0)->empty_idx;

        Component_Manager* component_manager = Component_Manager::get_instance();
        if ( component_manager == NULL ) {
            CHECK_INFO( 0, "Failed to get Component_Manager" );
            return ENGINE_ERROR;
        }

        // loop through all the components in arche and init the data location / check if data needs to be resized
        for (int i = 0; i < tmp_archetype_node->comp_nodes_vec->size(); i++) {
            // check to see if we need to resize data
            if ( tmp_archetype_node->comp_nodes_vec->at(i)->empty_idx == tmp_archetype_node->comp_nodes_vec->at(i)->total_elements ) {
                CHECK ( 0 );//expand_comp_node(&(archetype_nodes[arche_idx->second].comp_nodes_vec[i]));
            }

            // call the allocator for this component ( because C++ sucks )
            size_t comp_size = component_manager->get_component_size(tmp_archetype_node->comp_nodes_vec->at(i)->component_id);
            component_create_function init_func = component_manager->get_component_create(tmp_archetype_node->comp_nodes_vec->at(i)->component_id);
            init_func((tmp_archetype_node->comp_nodes_vec->at(i)->data + (entity_idx * comp_size)));
            tmp_archetype_node->comp_nodes_vec->at(i)->empty_idx += 1;
        }

        return SUCCESS;
    }

    CHECK_INFO( arche_idx == entity_archetype_manager->archetype_map->end(), "Archetype " << archetype_name << " is not registered" );

    return ARCHETYPE_DOES_NOT_EXIST;
}

uint8_t* Entity_Archetype_Manager::get_component_data( Entity entity, uint64_t component_id )
{
    CHECK( entity_archetype_manager != NULL );

    // get arche idx that this entity belongs to.
    std::unordered_map<uint64_t, uint64_t>::const_iterator entity_idx = entity_archetype_manager->entity_map->find(entity.id);
    if ( entity_idx != entity_archetype_manager->entity_map->end() ) {
        archetype_node_t* tmp_archetype_node = entity_archetype_manager->archetype_nodes->at(entity_idx->second);

        // get the comp idx for the passed component ID
        std::unordered_map<uint64_t, uint64_t>::const_iterator comp_idx = tmp_archetype_node->comp_map->find(component_id);
        if ( comp_idx != tmp_archetype_node->comp_map->end() ) {

            arche_comp_node_t* tmp_comp_node = tmp_archetype_node->comp_nodes_vec->at(comp_idx->second);

            // get the entity offset in the comp data chunk
            std::unordered_map<uint64_t, uint64_t>::const_iterator entity_comp_idx = tmp_archetype_node->entity_map->find(entity.id);

            uint8_t* return_data = tmp_comp_node->data;
            size_t comp_size = Component_Manager::get_instance()->get_component_size(component_id); //TODO(JOSH): add comp size to the comp_node
            return (return_data + (entity_comp_idx->second * comp_size));
        }
        CHECK_INFO( comp_idx == archetype_nodes[entity_idx->second].comp_map.end(),
                    "Component ID " << component_id << " not a part or this archetype" );
    }

    CHECK_INFO( entity_idx == entity_map.end(), "Entity ID " << entity.id << "is not a valid entity" );

    return NULL;
}

} // end namespace core
