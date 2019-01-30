#include <string>
#include "Engine.h"
#include "shader.h"

namespace Engine {

Vertex_Shader_Asset::Vertex_Shader_Asset()
{
    id = 0;
}

void Vertex_Shader_Asset::load( std::string file_path )
{
    load_shader_file(file_path, VERTEX_SHADER, &id);
}

} // end namespace Engine
