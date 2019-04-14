#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <inttypes.h>
#include <algorithm>
#include <cctype>
#include "header_parser.h"

static int generate_comp_id_header( std::ofstream& file, std::string comp_name )
{
    int rc = 0;

    file << "\ntemplate<> ENGINE_API Component_ID get_component_id<" << comp_name << ">( void );\n";

    return rc;
}

static int generate_comp_id_source( std::ofstream& file, std::string comp_name, uint32_t id )
{
    int rc = 0;

    file << "\ntemplate<> Component_ID get_component_id<" << comp_name << ">( void )\n";
    file << "{\n";
    file << "\treturn " << id << ";\n";
    file << "}\n";

    return rc;
}

int main( int argc, char* argv[] )
{
    std::string write_location;
    std::string file_name;
    std::vector<std::string> file_paths;
    std::vector<struct_def> comps;
    std::vector<std::string> includes;
    uint32_t last_gen_id = 1;

    if ( argc > 4 ) {
        file_paths.resize(argc - 3);

        write_location = argv[1];
        file_name = argv[2];

        for ( int ii = 3; ii < argc; ++ii ) {
            file_paths[ii - 3] = argv[ii];
        }

        parse_headers(&file_paths, &comps, &last_gen_id, &includes);
    }

    if ( comps.size () > 0 ) {
        std::ofstream h_file (write_location + "include/" + file_name + ".h");
        std::ofstream c_file (write_location + file_name + ".cpp");
        uint32_t starting_id = last_gen_id;

        if ( h_file.is_open() ) {
            std::string header_name = file_name;
            std::size_t h_pos = file_name.find(".h");

            for (std::string::size_type i=0; i<file_name.length(); ++i) {
                file_name[i] = (char)std::toupper(file_name[i]);
            }

            h_file << "#ifndef __" << file_name.substr(0, h_pos) <<"__\n#define __"<< file_name.substr(0, h_pos) <<"__\n\n";
            h_file << "#include \"core_common.h\" \n";

            for ( uint32_t jj = 0; jj < includes.size(); ++jj ) {
                h_file << "#include \"" << includes[jj] << "\" \n";
            }

            h_file << "\nnamespace Engine {\n";

            if ( last_gen_id == 1 ) {
                h_file << "\ntypedef uint32_t Component_ID;\n";
            }

            if ( last_gen_id == 1 ) {
                h_file << "\ntemplate<typename T> Component_ID get_component_id( void ) { return 0; }\n\n";
            }

            if ( last_gen_id == 1 ) {
                c_file << "#include \"base_generated_component_info.h\" \n\n";
            } else {
                c_file << "#include \"base_generated_component_info.h\" \n";
                c_file << "#include \"" << header_name << ".h\" \n\n";
            }

            c_file << "namespace Engine {\n";

            for ( uint32_t ii = 0; ii < comps.size(); ++ii ) {
                generate_comp_id_header(h_file, comps[ii].struct_name);
                generate_comp_id_source(c_file, comps[ii].struct_name, starting_id);

                starting_id += 1;
            }

            if ( last_gen_id == 1 ) {
                h_file << "\n#define LAST_INTERNAL_GEN_COMP_ID " << starting_id << "\n";
            }

            c_file << "\n} // end namespace Engine\n\n";
            h_file << "\n} // end namespace Engine\n\n";
            h_file << "#endif //__" << file_name.substr(0, h_pos) <<"__\n";
            h_file.close();
            c_file.close();
        }
    }
    return 0;
}
