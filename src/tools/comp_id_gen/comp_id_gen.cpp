#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <inttypes.h>
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
        std::ofstream file (write_location + file_name);
        uint32_t starting_id = last_gen_id;

        if ( file.is_open() ) {
            for ( uint32_t ii = 0; ii < comps.size(); ++ii ) {
                file << "#define COMPONENT_GEN_ID_" << comps[ii].struct_name << " " << starting_id << "\n";
                starting_id += 1;
            }

            if ( last_gen_id == 1 ) {
                file << "#define LAST_INTERNAL_GEN_COMP_ID " << starting_id << "\n";
            }

            file.close();
        }



    }

    return 0;
}
