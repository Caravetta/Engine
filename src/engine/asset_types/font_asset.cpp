#include "font_asset.h"

Font_Asset::Font_Asset()
{
    //do nothing
}

void Font_Asset::load( std::string file_path )
{
    font.load_font_file(file_path);
}
