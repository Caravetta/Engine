#include "vertex_shader_asset.h"

Vertex_Shader_Asset::Vertex_Shader_Asset()
{
    vertex_id = 0;
}

void Vertex_Shader_Asset::load( std::string file_path )
{
    core::load_shader_file(file_path, core::VERTEX_SHADER, &vertex_id);
}
