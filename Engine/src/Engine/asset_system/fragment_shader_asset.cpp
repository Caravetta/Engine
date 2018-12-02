#include <string>
#include "Engine.h"
#include "shader.h"

namespace Engine {

Fragment_Shader_Asset::Fragment_Shader_Asset()
{
    id = 0;
}

void Fragment_Shader_Asset::load( std::string file_path )
{
    load_shader_file(file_path, FRAGMENT_SHADER, &id);
}

} // end namespace Engine
