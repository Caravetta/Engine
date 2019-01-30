#ifndef __FUNCTION_PERF_H__
#define __FUNCTION_PERF_H__

#include <unordered_map>
#include "core_common.h"

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
    static Function_Perf* instance;
    std::vector<func_perf_data> perf_data;
    func_perf_data* root_node;
    func_perf_data* current_node;
    std::unordered_map<std::string, uint64_t>  func_name_map;

    void init();

public:
    static uint64_t func_current_type_idx;
    static Function_Perf* get_instance();
    void set_time_value( double time, std::string func_name );
    void set_current_node( std::string func_name );
    void print();
};

template <typename T>
uint64_t func_type_idx_info<T>::idx{Function_Perf::func_current_type_idx++};

#endif //__FUNCTION_PERF_H__
