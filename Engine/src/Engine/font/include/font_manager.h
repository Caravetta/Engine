#ifndef __FONT_MANAGER_H__
#define __FONT_MANAGER_H__

#include <string>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "core_common.h"

namespace Engine {

class Font_Manager {
private:
    static Font_Manager* instance;

    void init();

public:
    FT_Library ft;

    static Font_Manager* get_instance();
};

} // end namespace Engine

#endif //__FONT_MANAGER_H__
