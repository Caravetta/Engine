#include "system.h"

namespace Engine {

bool System::has_component( const u32 component_id )
{
    UNORDERED_MAP_ITERATOR(u64, u64) iter = comp_map.find(component_id);

    return (iter == comp_map.end() ? false : true);
}

bool System::pre_update( void )
{
    bool should_run = false;
    entity_count = 0;

    // check to see if this system is tracking any comps
    if ( component_nodes.size() > 0 ) {
        u64 total_count = 0;
        u64 current_idx = 0;
        component_node_t* current_comp = NULL;

        for (u64 ii = 0; ii < component_nodes.size(); ++ii) {
            total_count = 0;
            current_idx = 0;
            current_comp = &component_nodes[ii];

            current_comp->packed_data.clear();
            for ( u64 jj = 0; jj < current_comp->entity_count_vec.size(); ++jj ) {
                total_count += *(current_comp->entity_count_vec[jj]);
                current_comp->packed_data.resize(total_count);

                for ( u64 kk = 0; kk < *(current_comp->entity_count_vec[jj]); ++kk ) {
                    current_comp->packed_data[current_idx++] = &(current_comp->array_data_vec[jj]->at(current_comp->size * kk));
                }
            }
            entity_count = total_count;
        }

        if ( entity_count > 0 ) {
            should_run = true;
        }
    }

    return should_run;
}

void System::add_component_data( u64** enitiy_count, const u32 component_id, Array** data_array )
{
    UNORDERED_MAP_ITERATOR(u64, u64) comp_iter = comp_map.find(component_id);
    if ( comp_iter != comp_map.end() ) {

        CHECK_INFO( component_id == component_nodes[comp_iter->second].component_id,
                    "comp_id:" << component_id << " component_nodes[comp_idx->second].component_id:"
                    << component_nodes[comp_iter->second].component_id);

        component_nodes[comp_iter->second].entity_count_vec.push_back(*enitiy_count);
        component_nodes[comp_iter->second].array_data_vec.push_back(*data_array);
    }

    CHECK_INFO( comp_iter != comp_map.end(), "This comp ID:" << component_id << " is not tracked by " << name );
}

void System::add_component( const u32 component_id )
{
    add_component(component_id, COMPONENT_READ_AND_WRITE);
}

void System::add_component( const u32 component_id, const component_usage_t usage )
{
    if ( component_id < Component_Manager::get_max_components() ) {

        UNORDERED_MAP_ITERATOR(u64, u64) iter = comp_map.find(component_id);
        if ( iter == comp_map.end() ) {
            comp_map.insert({ component_id, component_nodes.size() });

            DEBUG_LOG("Adding comp ID " << component_id << " to " << name << " at " << component_nodes.size());

            component_node_t tmp_comp_node;
            tmp_comp_node.component_id = component_id;
            tmp_comp_node.usage = usage;
            tmp_comp_node.size = get_component_size(component_id);
            component_nodes.push_back(tmp_comp_node);
            component_list.push_back(component_id);

        } else {
            CHECK_INFO( 0, "Component ID:" << component_id << "already added" );
        }
    } else {
        LOG_ERROR("Component ID: " << component_id << " is not a valid component");
    }

    return;
}

std::vector<u8*>* System::get_data_vec( const u32 component_id )
{
    std::vector<u8*>* data = NULL;

    UNORDERED_MAP_ITERATOR(u64, u64) comp_iter = comp_map.find(component_id);
    if ( comp_iter != comp_map.end() ) {
        CHECK_INFO( comp_id == component_nodes[comp_iter->second].component_id,
                    "comp_id:" << comp_id << " component_nodes[comp_idx->second].component_id:"
                    << component_nodes[comp_idx->second].component_id );

        data = &component_nodes[comp_iter->second].packed_data;
    } else {
        CHECK_INFO( 0, "This comp ID:" << component_id << " is not tracked by " << name );
    }

    return data;
}

} // end namespace Engine
