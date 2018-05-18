#if !defined(TEXTURE_H)

#include "../core_common.h"

namespace core {

    class CORE_API Texture {
    public:
    unsigned char   *imageData;
    unsigned int    bpp;
    unsigned int    width;
    unsigned int    height;
    unsigned int    texID;
    unsigned int    type;

    Texture();
    };
} //end namespace core

#define TEXTURE_H
#endif
