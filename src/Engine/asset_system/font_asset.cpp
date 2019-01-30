#include "Engine_Types.h"
#include "Engine_Assets.h"
#include "font_manager.h"

namespace Engine {

Font_Asset::Font_Asset()
{
    //do nothing
}

void Font_Asset::load( std::string file_path )
{
    handle = Font_Manager::load_font_file(file_path);
}

} // end namespace Engine

