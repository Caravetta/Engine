#include "Engine.h"
#include "core_common.h"
#include "file_loader_utils.h"
#include "tga_file.h"

namespace Engine {

Texture_Asset::Texture_Asset()
{
    //Do Nothing
}

void Texture_Asset::load( std::string file_path )
{
    std::string file_type = get_file_type(file_path);

    if ( file_type == "tga" ) {
        if ( load_tga_file(file_path, &texture) != SUCCESS ) {
            LOG_ERROR("Failed to Load tga file: " << file_path);
        }

    } else {
        LOG_ERROR("Format (" << file_type << ") not supported");
    }
}

} // end namespace Engine
