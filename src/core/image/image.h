#if !defined(IMAGE_H)

#include <string>
#include <vector>
#include "../core_common.h"

namespace core {

typedef union {
    uint32_t color;
    struct {
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;
    };
} pixel_data_t;

    class CORE_API Image {
    public:
        int width;
        int height;
        uint32_t bits_per_pixel;
        std::vector<uint8_t> pixel_data;

        Image( std::string image_path );
        pixel_data_t get_RGB( int x, int y );
        bool alpha_channel() { return bits_per_pixel == 32; }
    };

} // end namespace core

#define IMAGE_H
#endif
