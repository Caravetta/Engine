#ifndef __FUNCTION_PERF_H__
#define __FUNCTION_PERF_H__

#include "../core_common.h"

#define SET_FUNC_NAME( store, name ) store = #name

typedef struct {
    std::string name;
    uint64_t    func_calls;
    double      total_time;
    double      max_time = 0;
} func_perf_data;

template <typename T>
struct func_type_idx_info {
    static uint64_t idx;
};

class Function_Perf {
private:
    CORE_API static Function_Perf* instance;
    std::vector<func_perf_data> perf_data;
    func_perf_data* root_node;
    func_perf_data* current_node;
    std::unordered_map<std::string, uint64_t>  func_name_map;

    void init();

public:
    CORE_API static uint64_t func_current_type_idx;
    static Function_Perf* get_instance();
    void set_time_value( double time, std::string func_name );
    void set_current_node( std::string func_name );
    void print();
};

template <typename T>
uint64_t func_type_idx_info<T>::idx{Function_Perf::func_current_type_idx++};

Function_Perf* Function_Perf::get_instance()
{
    if ( instance == NULL ) {
        LOG("Initializing Function_Perf");
        instance = new Function_Perf;
        instance->init();
    }

    return instance;
}

void Function_Perf::init()
{
    root_node = NULL;
}

void Function_Perf::set_time_value( double time, std::string func_name )
{
    uint64_t idx;

    std::unordered_map<std::string, uint64_t>::const_iterator func_name_idx = func_name_map.find(func_name);
    if ( func_name_idx != func_name_map.end() ) {
        idx = func_name_idx->second;
    } else {
        idx = perf_data.size();
        perf_data.push_back(func_perf_data());
        func_name_map.insert({ func_name, idx});
    }

    perf_data[idx].name = func_name;
    perf_data[idx].total_time += time;
    perf_data[idx].func_calls += 1;

    if (time > perf_data[idx].max_time) {
        perf_data[idx].max_time = time;
    }
}

void Function_Perf::set_current_node( std::string func_name )
{
#if 0
    if ( root_node == NULL ) {
        root_node = new func_perf_data;
        current_node = root_node;
        current_node->running_total = 0;
        current_node->num_calls = 0;
        current_node->parent = NULL;
        CHECK( current_node != NULL );
    } else {
        CHECK( current_node != NULL );
        //look to see if the current node knows about this node
        std::unordered_map<uint64_t, uint64_t>::const_iterator node_idx = current_node->func_map.find(func_type_idx_info<T>::idx);
        if ( node_idx == current_node->func_map.end() ) {
            //fist time seeing this node
            uint64_t cur_node_idx = current_node->child_nodes.size();
            current_node->func_map.insert({func_type_idx_info<T>::idx, cur_node_idx});
            func_perf_data tmp_data;
            current_node->child_nodes.push_back(tmp_data);
            func_perf_data* parent_node = current_node;
            current_node = &current_node->child_nodes[cur_node_idx];
            current_node->parent = parent_node;
            current_node->name = func_name;
        } else {
            //we have seen this node
            current_node = &current_node->child_nodes[node_idx->second];
        }
    }
#endif
}

void _print_node( func_perf_data* node, uint64_t offset )
{
    std::string star = "";
    for (uint64_t k = 0; k < offset; k++) {
        star += "-";
    }
    LOG(star << node->name << " Total_Time:" << node->total_time * 1000 << "ms Avg_Time:" <<
        (node->total_time / node->func_calls) * 1000 << "ms" << " Max:" << node->max_time * 1000 << " Call_Count:" << node->func_calls);
}

void Function_Perf::print()
{
    LOG("****************** TIME BLOCK START **************************");
    for (uint64_t i = 0; i < perf_data.size(); i++) {
        _print_node(&perf_data[i], 0);
        perf_data[i].total_time = 0;
        perf_data[i].func_calls = 0;
    }
    LOG("****************** TIME BLOCK END ****************************");
}

#endif //__FUNCTION_PERF_H__
