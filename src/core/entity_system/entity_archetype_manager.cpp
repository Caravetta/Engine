#include "entity_archetype_manager.h"

namespace core {

UhRC_t init_entity_archetype_manager( entity_archetype_manager_t* entity_archetype_manager )
{
    entity_archetype_manager = (entity_archetype_manager_t*)malloc(sizeof(entity_archetype_manager_t));
    if ( entity_archetype_manager == NULL ) {
        return MEMORY_ALLOC_FAILED;
    }

    entity_archetype_manager->entity_map = new (std::nothrow) std::unordered_map<uint64_t, uint64_t>;
    if ( entity_archetype_manager->entity_map == NULL ) {
        return MEMORY_ALLOC_FAILED;
    }

    entity_archetype_manager->archetype_map = new (std::nothrow) std::unordered_map<std::string, uint64_t>;
    if ( entity_archetype_manager->archetype_map == NULL ) {
        return MEMORY_ALLOC_FAILED;
    }

    entity_archetype_manager->archetype_nodes = new (std::nothrow) std::vector<archetype_node_t*>;
    if ( entity_archetype_manager->archetype_nodes == NULL ) {
        return MEMORY_ALLOC_FAILED;
    }

    return SUCCESS;
}

UhRC_t register_archetype( entity_archetype_manager_t* entity_archetype_manager, Entity_Archetype archetype, std::string archetype_name )
{
    std::vector<archetype_node_t*>* archetype_nodes = entity_archetype_manager->archetype_nodes;
    std::unordered_map<std::string, uint64_t>* archetype_map = entity_archetype_manager->archetype_map;

    std::unordered_map<std::string, uint64_t>::const_iterator arche_idx = archetype_map->find(archetype_name);
    if ( arche_idx == archetype_map->end() ) {

        uint64_t arche_node_idx = archetype_nodes->size();

        archetype_map->insert({ archetype_name, arche_node_idx });

        archetype_node_t* tmp_archetype_node = new (std::nothrow) archetype_node_t;
        CHECK( tmp_archetype_node != NULL );

        archetype_nodes->push_back(tmp_archetype_node);

        uint64_t comp_node_idx = 0;
        size_t comp_size = 0;


    }

    return SUCCESS;
}

Entity_Archetype_Manager* Entity_Archetype_Manager::instance = NULL;

Entity_Archetype_Manager* Entity_Archetype_Manager::get_instance()
{
    if ( instance == NULL ) {
        LOG("Initializing Entity_Archetype_Manager");
        instance = new Entity_Archetype_Manager;
    }

    return instance;
}

UhRC_t Entity_Archetype_Manager::register_archetype( Entity_Archetype archetype, std::string archetype_name )
{
    std::unordered_map<std::string, uint64_t>::const_iterator arche_idx = archetype_map.find(archetype_name);
    if ( arche_idx == archetype_map.end() ) {
        uint64_t arche_node_idx = archetype_nodes.size();

        archetype_map.insert({ archetype_name, arche_node_idx });

        archetype_nodes.reserve(100);
        archetype_nodes.push_back(archetype_node_t());

        uint64_t comp_node_idx = 0;
        size_t comp_size = 0;

        // loop through all comps for arche and create new comp nodes for them
        for (int i = 0; i < archetype.used_component_ids.size(); i++) {
            comp_node_idx = archetype_nodes[arche_node_idx].comp_nodes_vec.size();
            LOG(archetype_name << " " << archetype.used_component_ids[i]);
            // set mapping for comp ID to vec idx
            archetype_nodes[arche_node_idx].comp_map.insert({ archetype.used_component_ids[i], comp_node_idx });

            archetype_nodes[arche_node_idx].comp_nodes_vec.reserve(100);
            archetype_nodes[arche_node_idx].comp_nodes_vec.push_back(arche_comp_node_t());

            // setup the new component node
            archetype_nodes[arche_node_idx].comp_nodes_vec[comp_node_idx].total_elements = 10;
            archetype_nodes[arche_node_idx].comp_nodes_vec[comp_node_idx].empty_idx = 0;
            archetype_nodes[arche_node_idx].comp_nodes_vec[comp_node_idx].empty_idx_p = &(archetype_nodes[arche_node_idx].comp_nodes_vec[comp_node_idx].empty_idx);
            archetype_nodes[arche_node_idx].comp_nodes_vec[comp_node_idx].component_id = archetype.used_component_ids[i];

            comp_size = Component_Manager::get_instance()->get_component_size(archetype.used_component_ids[i]);

            archetype_nodes[arche_node_idx].comp_nodes_vec[comp_node_idx].data = (uint8_t*)malloc(comp_size * 10);
            archetype_nodes[arche_node_idx].comp_nodes_vec[comp_node_idx].data_p = &(archetype_nodes[arche_node_idx].comp_nodes_vec[comp_node_idx].data);
        }


        bool should_add = false;
        std::unordered_map<uint64_t, uint64_t>::const_iterator current_comp;

        // go through all systems to see if they care about this archetype
        for (int j = 0; j < System_Manager::get_instance()->systems.size(); j++) {
            should_add = true;

            // loop through all the system components
            for (int l = 0; l < System_Manager::get_instance()->systems[j]->component_list.size(); l++) {
                LOG("LOOKING FOR " << System_Manager::get_instance()->systems[j]->component_list[l]);
                current_comp = archetype_nodes[arche_node_idx].comp_map.find(System_Manager::get_instance()->systems[j]->component_list[l]);
                if ( current_comp == archetype_nodes[arche_node_idx].comp_map.end() ) {
                    LOG("HERE");
                    should_add = false;
                    break;
                }
            }

            if ( should_add == true ) {
                LOG("ADDING " << archetype_name << " to " << System_Manager::get_instance()->systems[j]->name);
                // loop through all the comp and add them to this system
                for (int k = 0; k < archetype_nodes[arche_node_idx].comp_nodes_vec.size(); k++) {
                    System_Manager::get_instance()->systems[j]->add_component_data(&archetype_nodes[arche_node_idx].comp_nodes_vec[k].data_p,
                                                                                   &archetype_nodes[arche_node_idx].comp_nodes_vec[k].empty_idx_p,
                                                                                   archetype_nodes[arche_node_idx].comp_nodes_vec[k].component_id);
                }
            }
        }

        return SUCCESS;
    }

    CHECK_INFO( arche_idx != archetype_map.end(), "Archetype " << archetype_name << " already exists." );

    return ARCHETYPE_EXISTS;
}

void Entity_Archetype_Manager::cleanup_archetypes()
{

}

void Entity_Archetype_Manager::expand_comp_node( arche_comp_node_t* component_node )
{
    CHECK_INFO( 0, "Not implemented" );
}

UhRC_t Entity_Archetype_Manager::add_entity( Entity entity, std::string archetype_name )
{
    std::unordered_map<std::string, uint64_t>::const_iterator arche_idx = archetype_map.find(archetype_name);
    if ( arche_idx != archetype_map.end() ) {
        uint64_t entity_idx = 0;

        // map entity id to arche idx
        entity_map.insert({ entity.id, arche_idx->second });

        // map entity id to data idx in comp data
        archetype_nodes[arche_idx->second].entity_map.insert({ entity.id, archetype_nodes[arche_idx->second].comp_nodes_vec[0].empty_idx });

        // map data idx to entity id
        archetype_nodes[arche_idx->second].idx_map.insert({ archetype_nodes[arche_idx->second].comp_nodes_vec[0].empty_idx, entity.id });

        entity_idx = archetype_nodes[arche_idx->second].comp_nodes_vec[0].empty_idx;

        // loop through all the components in arche and init the data location / check if data needs to be resized
        for (int i = 0; i < archetype_nodes[arche_idx->second].comp_nodes_vec.size(); i++) {
            // check to see if we need to resize data
            if ( archetype_nodes[arche_idx->second].comp_nodes_vec[i].empty_idx == archetype_nodes[arche_idx->second].comp_nodes_vec[i].total_elements ) {
                expand_comp_node(&(archetype_nodes[arche_idx->second].comp_nodes_vec[i]));
            }

            // call the allocator for this component ( because C++ sucks )
            size_t comp_size = Component_Manager::get_instance()->get_component_size(archetype_nodes[arche_idx->second].comp_nodes_vec[i].component_id);
            component_create_function init_func = Component_Manager::get_instance()->get_component_create(archetype_nodes[arche_idx->second].comp_nodes_vec[i].component_id);
            init_func((archetype_nodes[arche_idx->second].comp_nodes_vec[i].data + (entity_idx * comp_size)));
            archetype_nodes[arche_idx->second].comp_nodes_vec[i].empty_idx += 1;
        }

        return SUCCESS;
    }

    return ARCHETYPE_DOES_NOT_EXIST;
}

uint8_t* Entity_Archetype_Manager::get_component_data( Entity entity, uint64_t component_id )
{
    // get arche idx that this entity belongs to.
    std::unordered_map<uint64_t, uint64_t>::const_iterator entity_idx = entity_map.find(entity.id);
    if ( entity_idx != entity_map.end() ) {

        // get the comp idx for the passed component ID
        std::unordered_map<uint64_t, uint64_t>::const_iterator comp_idx = archetype_nodes[entity_idx->second].comp_map.find(component_id);
        if ( comp_idx != archetype_nodes[entity_idx->second].comp_map.end() ) {

            // get the entity offset in the comp data chunk
            std::unordered_map<uint64_t, uint64_t>::const_iterator entity_comp_idx = archetype_nodes[entity_idx->second].entity_map.find(entity.id);

            uint8_t* return_data = archetype_nodes[entity_idx->second].comp_nodes_vec[comp_idx->second].data;
            size_t comp_size = Component_Manager::get_instance()->get_component_size(component_id);
            return (return_data + (entity_comp_idx->second * comp_size));
        }
        CHECK_INFO( comp_idx == archetype_nodes[entity_idx->second].comp_map.end(),
                    "Component ID " << component_id << " not a part or this archetype" );
    }

    CHECK_INFO( entity_idx == entity_map.end(), "Entity ID " << entity.id << "is not a valid entity" );

    return NULL;
}

UhRC_t Entity_Archetype_Manager::remove_entity( Entity entity )
{
    CHECK_INFO( 0, "Not implemented" );
    return ENTITY_NOT_VALID;
}

} // end namespace core
