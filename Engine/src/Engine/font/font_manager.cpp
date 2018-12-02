#include "font_manager.h"

namespace Engine {

Font_Manager* Font_Manager::instance = NULL;

Font_Manager* Font_Manager::get_instance()
{
    if ( instance == NULL ) {
         instance = new Font_Manager();
         instance->init();
    }

    return instance;
}

void Font_Manager::init()
{
    if ( FT_Init_FreeType(&ft) ) {
         LOG_ERROR("Could not init freetype library");
    }
}

} // end namespace Engine
