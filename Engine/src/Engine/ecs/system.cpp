#include "system.h"

namespace Engine {

bool System::has_component( uint32_t component_id )
{
    std::unordered_map<uint64_t, uint64_t>::const_iterator ele = comp_map.find(component_id);

    return (ele == comp_map.end() ? false : true);
}

struct pre_update_job : public Job_Loop {
    std::vector<component_node_t>* volatile component_nodes;
    uint64_t ll;
    uint64_t oo;
    uint64_t current_idx;
    void Execute( uint64_t index ) {
        component_nodes->at(ll).packed_data[current_idx + index] = &(component_nodes->at(ll).array_data_vec[oo]->at(component_nodes->at(ll).size * index));
    }

};

bool System::pre_update()
{
    START_TIME_BLOCK(system_pre_update);
    entity_count = 0;

    // check to see if this system is tracking any comps
    if ( component_nodes.size() > 0 ) {
        uint64_t total_count = 0;
        uint64_t current_idx = 0;
        for (uint64_t ii = 0; ii < component_nodes.size(); ii++) {
            total_count = 0;
            component_nodes[ii].packed_data.clear();
            current_idx = 0;
            for (uint64_t jj = 0; jj < component_nodes[ii].entity_count_vec.size(); jj++) {
                total_count += *(component_nodes[ii].entity_count_vec[jj]);
                component_nodes[ii].packed_data.resize(total_count);
                for (uint64_t kk = 0; kk < *(component_nodes[ii].entity_count_vec[jj]); kk++) {
                    component_nodes[ii].packed_data[current_idx++] = &(component_nodes[ii].array_data_vec[jj]->at(component_nodes[ii].size * kk));
                }
            }
            entity_count = total_count;
        }

        if ( entity_count > 0 ) {
            END_TIME_BLOCK(system_pre_update);
            return true;
        }
    }

    END_TIME_BLOCK(system_pre_update);
    return false;
}

void System::add_component_data( uint64_t** entity_count, uint32_t component_id, Array** data_array )
{
    std::unordered_map<uint64_t, uint64_t>::const_iterator comp_idx = comp_map.find(component_id);
    if ( comp_idx != comp_map.end() ) {
        CHECK_INFO( component_id == component_nodes[comp_idx->second].component_id,
                    "comp_id:" << component_id << " component_nodes[comp_idx->second].component_id:" << component_nodes[comp_idx->second].component_id);
        component_nodes[comp_idx->second].entity_count_vec.push_back(*entity_count);
        component_nodes[comp_idx->second].array_data_vec.push_back(*data_array);
    }

    CHECK_INFO( comp_idx != comp_map.end(), "This comp ID:" << component_id << " is not tracked by " << name );
}

void System::add_component( uint32_t component_id )
{
    add_component(component_id, COMPONENT_READ_AND_WRITE);
}

void System::add_component( uint32_t component_id, component_usage_t usage )
{
    std::unordered_map<uint64_t, uint64_t>::const_iterator ele = comp_map.find(component_id);
    if ( ele == comp_map.end() ) {

        comp_map.insert({ component_id, component_nodes.size() });

        DEBUG_LOG("Adding comp ID " << component_id << " to " << name << " at " << component_nodes.size());

        component_node_t tmp_comp_node;
        tmp_comp_node.component_id = component_id;
        tmp_comp_node.usage = usage;
        tmp_comp_node.size = get_component_size(component_id);
        component_nodes.push_back(tmp_comp_node);
        component_list.push_back(component_id);


        return;
    }

    CHECK_INFO( ele != comp_map.end(), "Component ID:" << component_id << "already added" );
}

std::vector<uint8_t*>* System::get_data_vec( uint32_t component_id )
{
    std::unordered_map<uint64_t, uint64_t>::const_iterator comp_idx = comp_map.find(component_id);
    if ( comp_idx != comp_map.end() ) {
        CHECK_INFO( comp_id == component_nodes[comp_idx->second].component_id,
                    "comp_id:" << comp_id << " component_nodes[comp_idx->second].component_id:" << component_nodes[comp_idx->second].component_id);

        return &component_nodes[comp_idx->second].packed_data;
    }

    CHECK_INFO( comp_idx == comp_map.end(), "This comp ID:" << component_id << " is not tracked by " << name );

    return NULL;
}

} // end namespace Engine
