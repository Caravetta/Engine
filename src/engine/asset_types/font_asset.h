#if !defined(FONT_ASSET_H)

#include <string>
#include "../core/core.h"

class Font_Asset : public core::Asset {
public:
    core::Font font;

    Font_Asset();
    void load( std::string file_path );
};

#define FONT_ASSET_H
#endif
