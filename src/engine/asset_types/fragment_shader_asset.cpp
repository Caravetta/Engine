#include "fragment_shader_asset.h"

Fragment_Shader_Asset::Fragment_Shader_Asset()
{
    fragment_id = 0;
}

void Fragment_Shader_Asset::load( std::string file_path )
{
    core::load_shader_file(file_path, core::FRAGMENT_SHADER, &fragment_id);
}
