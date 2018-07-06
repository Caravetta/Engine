#if !defined(FONT_MANAGER_H)

#include <string>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "../core_common.h"

namespace core {

    class CORE_API Font_Manager {
    private:
        static Font_Manager* instance;

        void init();

    public:
        FT_Library ft;

        static Font_Manager* get_instance();
    };

} // end namespace core

#define FONT_MANAGER_H
#endif
