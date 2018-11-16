#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include "../core_common.h"
#include "../time/function_perf.h"
#include "../job_system/job.h"
#include "../job_system/job_manager.h"

namespace core {

typedef enum {
    COMPONENT_READ_ONLY         = 1 << 0,
    COMPONENT_WRITE_ONLY        = 1 << 1,
    COMPONENT_READ_AND_WRITE    = 1 << 2
} component_usage_t;

typedef struct {
    uint64_t                component_id;
    component_usage_t       usage;
    size_t                  size;
    std::vector<Array*>     array_data_vec;
    std::vector<uint64_t*>  entity_count_vec;
    std::vector<uint8_t*>   packed_data;
} component_node_t;

class System {
private:
    std::vector<component_node_t>           component_nodes;
    std::unordered_map<uint64_t, uint64_t>  comp_map;

protected:
    uint64_t entity_count = 0;

    void add_component( uint32_t component_id, component_usage_t usage );
    void add_component( uint32_t component_id );
    template<typename T> void add_component( component_usage_t usage );
    template<typename T> void add_component();
    template<typename T> T* get_data_at( uint64_t idx );
    template<typename T> std::vector<T*>* get_data_vec();

public:
    std::string             name;
    std::vector<uint64_t>   component_list;

    System(){};
    void add_component_data( uint64_t** enitiy_count, uint32_t comp_id, Array** data_array );
    bool has_component( uint32_t component_id );
    template<typename T> bool has_component();
    bool pre_update();

    virtual void init() = 0;
    virtual void update() = 0;
    virtual void shutdown() = 0;
};

bool System::has_component( uint32_t component_id )
{
    std::unordered_map<uint64_t, uint64_t>::const_iterator ele = comp_map.find(component_id);

    return (ele == comp_map.end() ? false : true);
}

template<typename T>
bool System::has_component()
{
    return has_component(Component_Manager::id<T>());
}

template<typename T>
T* System::get_data_at( uint64_t idx )
{
    //START_TIME_BLOCK(system_get_data_at);
    uint64_t comp_id = Component_Manager::id<T>();
    uint64_t comp_total = 0;
    T* return_data = NULL;

    // find the index that this comp is at.
    std::unordered_map<uint64_t, uint64_t>::const_iterator comp_idx = comp_map.find(comp_id);
    if ( comp_idx != comp_map.end() ) {

        CHECK_INFO( comp_id == component_nodes[comp_idx->second].component_id,
                    "comp_id:" << comp_id << " component_nodes[comp_idx->second].component_id:" << component_nodes[comp_idx->second].component_id);
        for ( int i = 0; i < component_nodes[comp_idx->second].entity_count_vec.size(); i++ ) {
            comp_total += *(component_nodes[comp_idx->second].entity_count_vec[i]);

            // if idx is less than comp_total then the data must be in this current comp_data node

            if ( idx < comp_total ) {
                END_TIME_BLOCK(system_get_data_at);
                return (T*)&(component_nodes[comp_idx->second].array_data_vec[i]->at(component_nodes[comp_idx->second].size * idx));
            }
        }

        CHECK_INFO( idx > comp_total, "idx:" << idx << " comp_total:" << comp_total);
    }

    CHECK_INFO( comp_idx == comp_map.end(), "This comp ID:" << comp_id << " is not tracked by " << name );

    //END_TIME_BLOCK(system_get_data_at);
    return return_data;
}

template<typename T>
std::vector<T*>* System::get_data_vec()
{
    //START_TIME_BLOCK(system_get_data_vec);
    uint64_t comp_id = Component_Manager::id<T>();

    std::unordered_map<uint64_t, uint64_t>::const_iterator comp_idx = comp_map.find(comp_id);
    if ( comp_idx != comp_map.end() ) {
        CHECK_INFO( comp_id == component_nodes[comp_idx->second].component_id,
                    "comp_id:" << comp_id << " component_nodes[comp_idx->second].component_id:" << component_nodes[comp_idx->second].component_id);

        //END_TIME_BLOCK(system_get_data_vec);
        return (std::vector<T*>*)&component_nodes[comp_idx->second].packed_data;
    }

    CHECK_INFO( comp_idx == comp_map.end(), "This comp ID:" << comp_id << " is not tracked by " << name );

    //END_TIME_BLOCK(system_get_data_vec);
    return NULL;
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

void System::add_component_data( uint64_t** enitiy_count, uint32_t component_id, Array** data_array )
{
    std::unordered_map<uint64_t, uint64_t>::const_iterator comp_idx = comp_map.find(component_id);
    if ( comp_idx != comp_map.end() ) {
        CHECK_INFO( component_id == component_nodes[comp_idx->second].component_id,
                    "comp_id:" << component_id << " component_nodes[comp_idx->second].component_id:" << component_nodes[comp_idx->second].component_id);
        component_nodes[comp_idx->second].entity_count_vec.push_back(*enitiy_count);
        component_nodes[comp_idx->second].array_data_vec.push_back(*data_array);
    }

    CHECK_INFO( comp_idx != comp_map.end(), "This comp ID:" << component_id << " is not tracked by " << name );
}

void System::add_component( uint32_t component_id )
{
    add_component(component_id, COMPONENT_READ_AND_WRITE);
}

template<typename T>
void System::add_component( component_usage_t usage )
{
    add_component(Component_Manager::id<T>(), usage);
}

template<typename T>
void System::add_component()
{
    add_component(Component_Manager::id<T>(), COMPONENT_READ_AND_WRITE);
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
        tmp_comp_node.size = Component_Manager::get_component_size(component_id);
        component_nodes.push_back(tmp_comp_node);
        component_list.push_back(component_id);


        return;
    }

    CHECK_INFO( ele != comp_map.end(), "Component ID:" << component_id << "already added" );
}

} // end namespace core

#endif // __SYSTEM_H__
