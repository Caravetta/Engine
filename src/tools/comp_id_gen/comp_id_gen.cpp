#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <inttypes.h>
#include <algorithm>
#include <cctype>
#include "header_parser.h"

int main( int argc, char* argv[] )
{
    std::string write_location;
    std::string file_name;
    std::vector<std::string> file_paths;
    std::vector<struct_def> comps;
    uint32_t last_gen_id = 1;

    if ( argc > 4 ) {
        file_paths.resize(argc - 3);

        write_location = argv[1];
        file_name = argv[2];

        for ( int ii = 3; ii < argc; ++ii ) {
            file_paths[ii - 3] = argv[ii];
        }

        parse_headers(&file_paths, &comps, &last_gen_id);
    }

    if ( comps.size () > 0 ) {
        std::ofstream h_file (write_location + "include/" + file_name + ".h");
        std::ofstream c_file (write_location + file_name + ".cpp");
        uint32_t starting_id = last_gen_id;

        if ( h_file.is_open() ) {
            std::size_t h_pos = file_name.find(".h");

            for (std::string::size_type i=0; i<file_name.length(); ++i) {
                file_name[i] = (char)std::toupper(file_name[i]);
            }

            h_file << "#ifndef __" << file_name.substr(0, h_pos) <<"__\n#define __"<< file_name.substr(0, h_pos) <<"__\n\n";
            h_file << "#include \"entity.h\" \n";
            h_file << "#include \"core_common.h\" \n";
            h_file << "\ntemplate<typename T> uint32_t get_component_id( void ) { return 0; }\n\n";

            for ( uint32_t ii = 0; ii < comps.size(); ++ii ) {
                //h_file << "#define COMPONENT_GEN_ID_" << comps[ii].struct_name << " " << starting_id << "\n";
                h_file << "template<> ENGINE_API uint32_t get_component_id<Engine::" << comps[ii].struct_name << ">( void );\n\n";

                c_file << "#include \"base_generated_component_info.h\" \n\n";
                c_file << "template<> uint32_t get_component_id<Engine::" << comps[ii].struct_name << ">( void )\n";
                c_file << "{\n";
                c_file << "\treturn " << starting_id << ";\n";
                c_file << "}\n\n";

                starting_id += 1;
            }

            if ( last_gen_id == 1 ) {
                h_file << "#define LAST_INTERNAL_GEN_COMP_ID " << starting_id << "\n";
            }

            h_file << "\n#endif //__" << file_name.substr(0, h_pos) <<"__\n";
            h_file.close();
            c_file.close();
        }
    }
    return 0;
}
