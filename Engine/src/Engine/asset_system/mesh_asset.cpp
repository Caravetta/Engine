#include <fstream>
#include "Engine.h"
#include "core_common.h"
#include "file_loader_utils.h"
#include "obj_file.h"

namespace Engine {

Mesh_Asset::Mesh_Asset()
{
    //Do nothing
}

void Mesh_Asset::load( std::string file_path )
{
    std::string file_type = get_file_type(file_path);

    if ( file_type == "mesh" ) {
        std::ifstream input_file(file_path, std::ios::binary);
        mesh.deserialize(&input_file);
        input_file.clear();
        input_file.close();
    } else if ( file_type == "obj" ) {
        if ( load_obj_file(file_path, &mesh) != SUCCESS ) {
            LOG_ERROR("Failed to Load obj file: " << file_path);
        }
    } else {
        LOG_ERROR("Format (" << file_type << ") not supported");
    }
}

} // end namespace Engine

