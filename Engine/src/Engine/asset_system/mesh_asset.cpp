#include <fstream>
#include "Engine.h"

namespace Engine {

Mesh_Asset::Mesh_Asset()
{
    //Do nothing
}

void Mesh_Asset::load( std::string file_path )
{
    std::ifstream input_file(file_path, std::ios::binary);
    mesh.deserialize(&input_file);
    input_file.clear();
    input_file.close();
}

} // end namespace Engine

