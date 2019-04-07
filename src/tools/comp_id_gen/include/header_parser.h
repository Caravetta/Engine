#ifndef __HEADER_PARSER_H__
#define __HEADER_PARSER_H__

#include <string>
#include <vector>

struct struct_member {
    std::string type;
    std::string name;
    bool is_pointer;
};

struct struct_def {
    std::string struct_name;
    std::vector<struct_member> members;
};

int parse_headers( std::vector<std::string>* file_paths, std::vector<struct_def>* comps, uint32_t* max_gen_id );


#endif //__HEADER_PARSER_H__
