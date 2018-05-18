#include "mesh_asset.h"

Mesh_Asset::Mesh_Asset()
{
    //Do nothing
}

void Mesh_Asset::load( std::string file_path )
{
    std::ifstream input_file(file_path, std::ios::binary);
    this->mesh.deserialize(&input_file);
    input_file.clear();
    input_file.close();
}
